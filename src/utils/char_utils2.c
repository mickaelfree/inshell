/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:35:26 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/07 01:35:28 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
