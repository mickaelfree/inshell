/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:35:59 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/18 15:46:17 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

int iswhitespace(char c)
{
        return(c && ((c >= 9 && c <= 13) || c == ' '));
}
int isoperator(char c)
{
        return(c == '|' || c == '>' || c == '<');
}
int ispipe(char c)
{
        return(c == '|');
}
int isredir(char c)
{
        return(c == '>' || c == '<');
}
int isescape(char c)
{
        return(c == '\\');
}
int isquote(char c)
{
        return(c == '"' || c == '\'');
}
int isspecial(char c)
{
        return(c == ';' || c == '&' || c == '(' || c == ')' || c == '$');
}
