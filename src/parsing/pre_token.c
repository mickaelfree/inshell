/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:00:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/18 18:17:43 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"
//INFO:
//separer en fonction des etats 
//double quote = tant que je trouve pas de nouvel " jidentifie tout comme quoted 
//operateur separer la commande 
char *type_token []= {"NORMAL","WHITESPACE","PIPE","REDIR","QUOTE","ESCAPE","SPECIAL"};

void ft_state(char c ,int *i)
{
        if (c == '"')
                *i = 2;
        else if (is_whitespace(c))
                *i = 1;
        else if (is_operator(c))
                *i = 3;
        else
                *i = 0;
}
void pre_token(char *line)
{
        t_pre_token token;
        int state;
        int prevous_state;
        int i;
        i = 0;
        state = 0;
        prevous_state= 1;

         while(*line&&is_whitespace(*line))
                 line++;

                printf("{");

        //INFO:
        //objetif determiner les changement de type  
        //commen on fait pour faire un zero coppi en troncan la partie indesirable >> fwrite peut imprimer en fonction de la len
        //stock le tout dans un liste chainer
        while(line[i])
        {
                if (state != prevous_state)
                {
                        printf(" %s",type_token[state]);
                        prevous_state = state;
                }
                state = char_type(line[i]);
                i++;
        }
                printf("}\n");

        token.len = strlen(line);
        token.start = line;
        token.next = NULL;

}
