/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:35:59 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/07 01:38:45 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

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
