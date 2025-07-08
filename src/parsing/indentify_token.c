/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indentyfy_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:00:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/20 19:51:54 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"
//INFO:
//separer en fonction des etats 
//double quote = tant que je trouve pas de nouvel " jidentifie tout comme quoted 
//operateur separer la commande 
char *type_token []= {"NORMAL","WHITESPACE","PIPE","REDIR","APPEND","HEREDOC","SINGLE_QUOTE","DOUBLE_QUOTE","ESCAPE","SPECIAL"};


t_pre_token *identify_token(char *line)
{
    t_pre_token *head = NULL;
    t_pre_token *current = NULL;
    char *ptr = line;
    char *token_start;
    int state, prev_state;
    
    skip_whitespace(&ptr);
    token_start = ptr;
    state = char_type(ptr);
    prev_state = state;
        if(state== CHAR_APPEND || state == CHAR_HEREDOC)
                ptr++;
    while (*ptr)
    {
        state = char_type(ptr);
        if (state != prev_state)
        {
            if (!add_new_token(&head, &current, token_start, 
                              ptr - token_start, prev_state))
                return NULL;
            token_start = ptr;
            prev_state = state;
                        if(state== CHAR_APPEND || state == CHAR_HEREDOC)
                ptr++;
        }
        ptr++;
    }
    if (ptr > token_start) {
        if (!add_new_token(&head, &current, token_start, 
                          ptr - token_start, prev_state))
            return NULL;
    }
        //print_token(head);
    return head;
}
void print_token(t_pre_token *token)
{
    printf("print_token called from: %p\n", __builtin_return_address(0));
    while (token)
    {
        printf("Token: %.*s (%s)\n", token->len, token->start, type_token[token->type]);
        token = token->next;
    }
}
