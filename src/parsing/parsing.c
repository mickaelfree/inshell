/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:52:34 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/20 20:15:11 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/inshell.h"

int check_quotes(t_pre_token *head)
{
    int quote_count = 0;
    while (head)
    {
        if (head->type == CHAR_SINGLE_QUOTE || head->type == CHAR_DOUBLE_QUOTE)
            quote_count++;
        head = head->next;
    }
    if (quote_count % 2 != 0)
    {
        printf("Unmatched quotes");
        return (1);
    }
    return (0);
}
int parse_token(char *line)
{
    t_pre_token *head = identify_token(line);
    if (!head)
        return 0;
    if(!(check_quotes(head)))
           return 0;
    // TODO: implement parsing logic
    //free_token_list(head);
    return 1;
}
