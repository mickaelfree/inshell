/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:35:59 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/18 16:19:57 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

int	is_whitespace(char c)
{
	return (c && ((c >= 9 && c <= 13) || c == ' '));
}
int	is_pipe(char c)
{
	return (c == '|');
}
int	is_redir(char c)
{
	return (c == '>' || c == '<');
}
int	is_append(char *c)
{
	if (!c[1])
		return (0);
	return (c[0] == '>' && c[1] == '>');
}
int	is_heredoc(char *c)
{
	if (!c[1])
		return (0);
	return (c[0] == '<' && c[1] == '<');
}
int	is_escape(char c)
{
	return (c == '\\');
}
int	is_quote(char c)
{
	return (is_single_quote(c) || is_double_quote(c));
}
int	is_double_quote(char c)
{
	return (c == '"');
}
int	is_single_quote(char c)
{
	return (c == '\'');
}
int	is_special(char c)
{
	return (c == ';' || c == '&' || c == '(' || c == ')' || c == '$');
}
int	is_operator(char c)
{
	return (is_pipe(c) || is_redir(c) || c == '<' || c == '>');
}
