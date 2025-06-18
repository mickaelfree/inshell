/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:35:59 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/18 15:52:20 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

int is_whitespace(char c)
{
        return(c && ((c >= 9 && c <= 13) || c == ' '));
}
int is_operator(char c)
{
        return(c == '|' || c == '>' || c == '<');
}
int is_pipe(char c)
{
        return(c == '|');
}
int is_redir(char c)
{
        return(c == '>' || c == '<');
}
int is_escape(char c)
{
        return(c == '\\');
}
int is_quote(char c)
{
        return(c == '"' || c == '\'');
}
int is_special(char c)
{
        return(c == ';' || c == '&' || c == '(' || c == ')' || c == '$');
}
