/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:12:14 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/14 21:54:29 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"

void	init_command(t_command *cmd)
{
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_delim = NULL;
	cmd->append_mode = 0;
	cmd->redirections = NULL;
	cmd->next = NULL;
}

static void	add_redirection_to_list(t_command *cmd, int type, char *filename)
{
	t_redirection	*new_redir;
	t_redirection	*current;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->filename = filename;
	new_redir->append_mode = (type == TOKEN_APPEND) ? 1 : 0;
	new_redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}
char	*expand_variables_with_quote(char *str, char **envp, int quote_type)
{
	int	len;

	(void)quote_type;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (ft_strdup(str));
	return (expand_variables(str, envp));
}

static void	add_argument(t_command *cmd, char *value, char **envp)
{
	char	*expanded_value;
	char	**new_args;
	int		i;
	char	*temp;

	expanded_value = expand_variables_with_quote(value, envp, 0);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	if (!expanded_value)
		return ;
	temp = expanded_value;
	expanded_value = remove_quotes(expanded_value, ft_strlen(expanded_value));
	free(temp);
	if (!expanded_value)
		return ;
	new_args = malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
        {
                free(expanded_value);
                free(value);
		return ;
        }
	i = 0;
	while (i < cmd->arg_count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[cmd->arg_count] = expanded_value;
	new_args[cmd->arg_count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->arg_count++;
        free(value);
}

int	handle_redirection(t_command *cmd, t_pre_token **token, char **envp)
{
	int		type;
	char	*value;
	char	*expanded_value;
	char	*temp2;

	type = (*token)->type;
	*token = (*token)->next;
	if (!*token || ((*token)->type != TOKEN_WORD
			&& (*token)->type != TOKEN_QUOTED
			&& (*token)->type != TOKEN_DOUBLE_QUOTE
			&& (*token)->type != TOKEN_SINGLE_QUOTE))
	{
		printf("Syntax error: missing file after redirection\n");
		return (0);
	}
	value = ft_strndup((*token)->start, (*token)->len);
	expanded_value = expand_variables_with_quote(value, envp, 0);
	temp2 = expanded_value;
	expanded_value = remove_quotes(expanded_value, ft_strlen(expanded_value));
	free(temp2);
	free(value);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	add_redirection_to_list(cmd, type, expanded_value);
	*token = (*token)->next;
	return (1);
}
static void	remove_empty_commands(t_command **head)
{
	t_command	*prev;
	t_command	*current;
	t_command	*to_free;

	prev = NULL;
	current = *head;
	while (current)
	{
		if (current->arg_count == 0 && !current->redirections)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			to_free = current;
			current = current->next;
			free(to_free);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
t_command	*build_pipeline(t_pre_token *tokens, char **envp)
{
	t_command	*head;
	t_command	*current;
	t_pre_token	*token;
	t_command	*new_cmd;
	char		*value;
	char		*expanded_value;
	char		*trimmed;

	head = NULL;
	current = NULL;
	token = tokens;
	while (token)
	{
		if (!current || token->type == TOKEN_PIPE)
		{
			new_cmd = malloc(sizeof(t_command));
			if (!new_cmd)
			{
				ft_free_commands(head);
				return (NULL);
			}
			init_command(new_cmd);
			if (!head)
				head = new_cmd;
			else
				current->next = new_cmd;
			current = new_cmd;
			if (token->type == TOKEN_PIPE)
			{
				token = token->next;
				if (!token)
				{
					printf("Syntax error: pipe at end\n");
					ft_free_commands(head);
					return (NULL);
				}
				continue ;
			}
		}
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		{
			if (!handle_redirection(current, &token, envp))
			{
				ft_free_commands(head);
				return (NULL);
			}
		}
		else if (token->type == TOKEN_WORD || token->type == TOKEN_QUOTED
				|| token->type == TOKEN_DOUBLE_QUOTE
				|| token->type == TOKEN_SINGLE_QUOTE)
		{
			value = ft_strndup(token->start, token->len);
			expanded_value = expand_variables_with_quote(value, envp, 0);
			if (!expanded_value)
				expanded_value = ft_strdup("");
			trimmed = expanded_value;
			while (*trimmed == ' ' || *trimmed == '\t')
				trimmed++;
			if (*trimmed != '\0')
				add_argument(current, value, envp);
			free(value);
			free(expanded_value);
			token = token->next;
		}
		else
		{
			token = token->next;
		}
	}
        remove_empty_commands(&head);
        	return (head);

}
