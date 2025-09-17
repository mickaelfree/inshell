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
	if (type == TOKEN_APPEND)
		new_redir->append_mode = 1;
	else
		new_redir->append_mode = 0;
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
	char	*result;
	size_t	i;
	size_t	start;
	int		in_single;
	int		in_double;
	char	*segment;
	char	*tmp;
	char	*expanded;

	(void)quote_type;
	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			if (i > start)
			{
				segment = ft_strndup(str + start, i - start);
				if (in_single)
					expanded = ft_strdup(segment);
				else
					expanded = expand_variables(segment, envp);
				tmp = result;
				if (expanded)
				{
					result = ft_strjoin(result, expanded);
					free(expanded);
				}
				else
					result = ft_strjoin(result, segment);
				free(tmp);
				free(segment);
			}
			in_single = !in_single;
			start = i + 1;
			i++;
			continue ;
		}
		if (str[i] == '\"' && !in_single)
		{
			if (i > start)
			{
				segment = ft_strndup(str + start, i - start);
				expanded = expand_variables(segment, envp);
				tmp = result;
				if (expanded)
				{
					result = ft_strjoin(result, expanded);
					free(expanded);
				}
				else
					result = ft_strjoin(result, segment);
				free(tmp);
				free(segment);
			}
			in_double = !in_double;
			start = i + 1;
			i++;
			continue ;
		}
		i++;
	}
	if (start < ft_strlen(str))
	{
		segment = ft_strndup(str + start, ft_strlen(str) - start);
		if (in_single)
			expanded = ft_strdup(segment);
		else
			expanded = expand_variables(segment, envp);
		tmp = result;
		if (expanded)
		{
			result = ft_strjoin(result, expanded);
			free(expanded);
		}
		else
			result = ft_strjoin(result, segment);
		free(tmp);
		free(segment);
	}
	return (result);
}

static void	add_argument(t_command *cmd, char *value, char **envp)
{
	char	*expanded_value;
	char	**new_args;
	int		i;

	expanded_value = expand_variables_with_quote(value, envp, 0);
	if (!expanded_value)
		expanded_value = ft_strdup("");
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

t_command   *build_pipeline(t_pre_token *tokens, char **envp)
{
    t_command   *head;
    t_command   *current;
    t_pre_token *token;
    t_command   *new_cmd;
    char        *value;
    char        *expanded_value;
    char        *trimmed;

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
            continue ;
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
            else
                free(value);
            free(expanded_value);
            token = token->next;
        }
        else
        {
            /* autre type de token (espace, etc.) */
            token = token->next;
        }
    }
    return (head);
}

