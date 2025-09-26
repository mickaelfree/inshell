/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:35:56 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/19 22:58:51 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

int	is_operator(char c)
{
	return (is_pipe(c) || is_redir(c) || c == '<' || c == '>');
}

void	skip_whitespace(char **line)
{
	while (**line && is_whitespace((unsigned char)**line))
		(*line)++;
}

char	*skip_charset(char *str, char charset)
{
	while (*str == charset)
		str++;
	return (str);
}

int	char_type(char *c)
{
	if (is_whitespace(*c))
		return (CHAR_WHITESPACE);
	else if (is_single_quote(*c))
		return (CHAR_SINGLE_QUOTE);
	else if (is_heredoc(c))
		return (CHAR_HEREDOC);
	else if (is_append(c))
		return (CHAR_APPEND);
	else if (is_double_quote(*c))
		return (CHAR_DOUBLE_QUOTE);
	else if (is_pipe(*c))
		return (CHAR_PIPE);
	else if (is_redir(*c))
		return (CHAR_REDIR);
	else if (is_escape(*c))
		return (CHAR_ESCAPE);
	else if (is_special(*c))
		return (CHAR_SPECIAL);
	else
		return (CHAR_NORMAL);
}

char	*get_key(char *var)
{
	char	*k_end;

	k_end = ft_strchr(var, '=');
	if (!k_end)
		return (ft_strdup(var));
	return (ft_strndup(var, k_end - var));
}
