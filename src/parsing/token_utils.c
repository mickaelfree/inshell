/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:48:37 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/18 18:21:11 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"

static inline void skip_whitespace(char **line)

{
    while (**line && is_whitespace((unsigned char)**line))
        (*line)++;
}

int char_type(char c)
{
    if (is_whitespace(c))
        return (CHAR_WHITESPACE);
    else if (is_quote(c))
        return (CHAR_QUOTE);
    else if (is_pipe(c))
        return (CHAR_PIPE);
    else if (is_redir(c))
        return (CHAR_REDIR);
    else if (is_escape(c))
        return (CHAR_ESCAPE);
    else if (is_special(c))
        return (CHAR_SPECIAL);
    else
        return (CHAR_NORMAL);
}
// int main(void)
// {
//         char *line = "ls -l | grep test > output.txt";
//         int i = 0;
//         while (line[i])
//         {
//                 printf("%d", char_type(line[i]));
//                 i++;
//         }
//         return (0);
// }
