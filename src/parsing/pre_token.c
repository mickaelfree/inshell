/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:00:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/15 18:40:38 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"
#include <ctype.h>
#include <stdio.h>
//INFO:
//separer en fonction des etats 
//double quote = tant que je trouve pas de nouvel " jidentifie tout comme quoted 
//operateur separer la commande 
int iswhitespace(char c)
{
        return(c && ((c >= 9 && c <= 13) || c == ' '));
}
int isoperator(char c)
{
        return(c == '|' || c == '>' || c == '<');
}
void ft_state(char c ,int *i)
{
        if (c == '"')
                *i = 2;
        else if (iswhitespace(c))
                *i = 1;
        else if (isoperator(c))
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

         while(*line&&iswhitespace(*line))
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
                        printf(" %d",prevous_state);
                        prevous_state = state;
                }
                ft_state(line[i],&state);
                i++;
        }
                printf("}\n");

        token.len = strlen(line);
        token.start = line;
        token.next = NULL;

}
