/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:12:14 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/07 01:49:32 by zsonie           ###   ########lyon.fr   */
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
	cmd->next = NULL;
}
char	*expand_variables_with_quote(char *str, char **envp, int quote_type)
{
	if (quote_type == TOKEN_SINGLE_QUOTE)
		return (ft_strdup(str));
	return (expand_variables(str, envp));
}

static void	add_argument(t_command *cmd, char *value, char **envp,int quote_type)
{
	char	*expanded_value;
	char	**new_args;
	int		i;

	expanded_value = expand_variables_with_quote(value, envp,quote_type);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	new_args = malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
		return ;
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

	type = (*token)->type;
	*token = (*token)->next;
	if (!*token || ((*token)->type != TOKEN_WORD
			&& (*token)->type != TOKEN_DOUBLE_QUOTE && (*token)->type != TOKEN_SINGLE_QUOTE))
	{
		printf("Syntax error: missing file after redirection\n");
		return (0);
	}
	value = strndup((*token)->start, (*token)->len);
	expanded_value = expand_variables(value, envp);
	free(value);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	if (type == TOKEN_REDIR_IN)
	{
		if (cmd->input_file)
		{
			// FIX:temporaire erreur 66;
			// printf("Warning: multiple input redirections, last wins\n");
			g_last_exit_status = 1;
			free(cmd->input_file);
		}
		cmd->input_file = expanded_value;
	}
	else if (type == TOKEN_REDIR_OUT || type == TOKEN_APPEND)
	{
		if (cmd->output_file)
		{
			// FIX:temporaire erreur 88;
			// printf("Warning: multiple output redirections, last wins\n");
			g_last_exit_status = 1;
			free(cmd->output_file);
		}
		cmd->output_file = expanded_value;
		cmd->append_mode = (type == TOKEN_APPEND) ? 1 : 0;
	}
	else if (type == TOKEN_HEREDOC)
	{
		if (cmd->heredoc_delim)
		{
			printf("Warning: multiple heredoc, last wins\n");
			free(cmd->heredoc_delim);
		}
		cmd->heredoc_delim = expanded_value;
	}
	else
		free(expanded_value);
	return (1);
}

t_command	*build_pipeline(t_pre_token *tokens, char **envp)
{
	t_command	*head;
	t_command	*current;
	t_pre_token	*token;
	t_command	*new_cmd;
	char		*value;

	head = NULL;
	current = NULL;
	token = tokens;
	while (token)
	{
		if (!current || token->type == TOKEN_PIPE)
		{
			new_cmd = malloc(sizeof(t_command));
			if (!new_cmd)
				return (NULL);
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
					return (NULL);
				}
			}
		}
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		{
			if (!handle_redirection(current, &token, envp))
				return (NULL);
			token = token->next;
			continue ;
		}
		if (token->type == TOKEN_WORD || token->type == TOKEN_DOUBLE_QUOTE | token->type == TOKEN_SINGLE_QUOTE)
		{
			value = strndup(token->start, token->len);
			add_argument(current, value, envp,token->type);
		}
		token = token->next;
	}
	return (head);
}
