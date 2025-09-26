/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:26:37 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/23 22:06:30 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

static int	validate_redirection_token(t_pre_token *token)
{
	if (!token)
	{
		write(STDERR_FILENO, "syntax error: unexpected end of input\n", 38);
		g_last_exit_status = 2;
		return (0);
	}
	if (!can_handle_word(token))
	{
		write(STDERR_FILENO, "syntax error: missing file after redirection\n",
			46);
		g_last_exit_status = 2;
		return (0);
	}
	return (1);
}

static char	*process_filename(t_pre_token *token, char **envp)
{
	char	*value;
	char	*expanded_value;
	char	*temp;

	if (!token || !token->start)
		return (NULL);
	value = ft_strndup(token->start, token->len);
	if (!value)
	{
		write(STDERR_FILENO, "malloc error\n", 13);
		return (NULL);
	}
	expanded_value = expand_variables_with_quote(value, envp);
	free(value);
	if (!expanded_value)
		return (ft_strdup(""));
	temp = expanded_value;
	expanded_value = remove_quotes(expanded_value, ft_strlen(expanded_value));
	free(temp);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	return (expanded_value);
}

int	handle_redirection(t_command *cmd, t_pre_token **token, char **envp)
{
	int		type;
	char	*filename;

	if (!cmd || !token || !*token)
		return (0);
	type = (*token)->type;
	*token = (*token)->next;
	if (!validate_redirection_token(*token))
		return (0);
	filename = process_filename(*token, envp);
	if (!filename || !create_and_add_redirection(cmd, type, filename))
	{
		free(filename);
		return (0);
	}
	*token = (*token)->next;
	return (1);
}
