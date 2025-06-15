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
int iswhitespace(char c)
{
        return(c && ((c >= 9 && c <= 13) || c == ' '));
}
void ft_state(char c ,int *i)
{
        if(c =='"')
        {
          printf("q");
                if(*i==2)
                        *i =0;
                else
                        *i = 2;
                return;
        }
        if(isalnum(c)&& *i==0)
        {
          printf("n");
                return;
        }
        printf("q");



}
void pre_token(char *line)
{
        t_pre_token token;
        int state;
        int prevous_state;
        int i;
        i = 0;
        state = 0;
        prevous_state= 0;

         while(*line&&iswhitespace(*line))
                 line++;

                printf("{");
        while(line[i])
        {
                ft_state(line[i],&state);
                if(state != prevous_state)
                {
                        printf(" ");
                        prevous_state = state;
                }
                i++;
        }
                printf("}\n");

        token.len = strlen(line);
        token.start = line;
        token.next = NULL;
        

        printf(" %s\n",token.start);
        printf("%d\n",token.len);
        printf("%d\n",token.next); 

}
