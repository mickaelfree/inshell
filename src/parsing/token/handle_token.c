/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:27:29 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 20:07:53 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_parsing.h>
#include <ft_strings.h>
#include <stdio.h>
#include <stdlib.h>

static int	handle_redirection_token(t_command **current, t_pre_token **token,
		char **envp, t_command **head)
{
	(void)head;
	if (!handle_redirection(*current, token, envp))
		return (0);
	return (1);
}

static int	handle_pipe_token(t_command **current, t_pre_token **token,
		char **envp, t_command **head)
{
	t_command	*new_cmd;

	(void)head;
	(void)envp;
	*token = (*token)->next;
	if (!*token)
	{
		printf("Syntax error: pipe at end\n");
		return (0);
	}
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (0);
	init_command(new_cmd);
	(*current)->next = new_cmd;
	*current = new_cmd;
	return (1);
}

static int	handle_whitespace_quote_token(t_command **current,
		t_pre_token **token, char **envp, t_command **head)
{
	char	*value;
	char	**new_args;
	int		i;

	(void)head;
	(void)envp;
	value = ft_strndup((*token)->start + 1, (*token)->len - 2);
	new_args = malloc(sizeof(char *) * ((*current)->arg_count + 2));
	if (!new_args)
	{
		free(value);
		return (0);
	}
	i = -1;
	while (++i < (*current)->arg_count)
		new_args[i] = (*current)->args[i];
	new_args[(*current)->arg_count] = value;
	new_args[(*current)->arg_count + 1] = NULL;
	if ((*current)->args)
		free((*current)->args);
	(*current)->args = new_args;
	(*current)->arg_count++;
	*token = (*token)->next;
	return (1);
}

static int	handle_word_token(t_command **current, t_pre_token **token,
		char **envp, t_command **head)
{
	char	*value;
	char	*expanded_value;
	char	*trimmed;

	(void)head;
	value = ft_strndup((*token)->start, (*token)->len);
	expanded_value = expand_variables_with_quote(value, envp);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	trimmed = expanded_value;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (*trimmed != '\0')
		add_argument(*current, value, envp);
	else
		free(value);
	free(expanded_value);
	*token = (*token)->next;
	return (1);
}

void	init_handlers(t_token_handler *handlers)
{
	handlers[0] = (t_token_handler){can_handle_pipe, handle_pipe_token};
	handlers[1] = (t_token_handler){can_handle_redirection,
		handle_redirection_token};
	handlers[2] = (t_token_handler){can_handle_word, handle_word_token};
	handlers[3] = (t_token_handler){can_handle_whitespace_quote,
		handle_whitespace_quote_token};
	handlers[4] = (t_token_handler){NULL, NULL};
}
