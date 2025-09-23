/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:27:29 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/23 20:15:43 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

int	handle_redirection_token(t_command **current, t_pre_token **token,
		char **envp, t_command **head)
{
	(void)head;
	if (!handle_redirection(*current, token, envp))
		return (0);
	return (1);
}

int	handle_pipe_token(t_command **current, t_pre_token **token, char **envp,
		t_command **head)
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

int	handle_word_token(t_command **current, t_pre_token **token, char **envp,
		t_command **head)
{
	char	*value;
	char	*expanded_value;
	char	*trimmed;

	(void)head;
	value = ft_strndup((*token)->start, (*token)->len);
	expanded_value = expand_variables_with_quote(value, envp, 0);
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
	handlers[3] = (t_token_handler){NULL, NULL};
}

int	process_token(t_pre_token **token, t_command **current, t_command **head,
		char **envp)
{
	t_token_handler	handlers[4];
	int				i;

	init_handlers(handlers);
	i = 0;
	while (handlers[i].can_handle)
	{
		if (handlers[i].can_handle(*token))
			return (handlers[i].handle(current, token, envp, head));
		i++;
	}
	return (0);
}
