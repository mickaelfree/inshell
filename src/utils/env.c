/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:19:09 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/11 14:19:10 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ft_env(char **envp)
{
        int count_pointer;
        int count_char;
        int total;
        int i;

        i = 0;
        char **new_env;
        char *pool_string;
        count_pointer = 0;
        count_char= 0;

        while (envp[count_pointer])
        {
                count_char += strlen(envp[count_pointer] + 1);
                count_pointer++;
        }
        printf("le nombre de variable denviroment et de %d et donc il faut allouer %d de byte %lu \n",count_pointer,count_pointer, sizeof(char * ));
        printf("le nombre char %d\n",count_char);
        total = (sizeof(char *) * count_pointer )+ (sizeof(char) * count_char);
        printf("le total de la pool a louer et %d\n",total);
        new_env = malloc(total);
        pool_string = (char*)&new_env[count_pointer + 1];

        while(i < count_pointer)
        {
                new_env[i] = pool_string;
                total = strlen(envp[i] +1);
                memcpy(pool_string,envp[i],total);
                i++;
                pool_string +=total;
        }
        new_env[count_pointer] = NULL;
        while(*new_env)
                printf("%s",*new_env++);
        return 0;
}
/* 
int main(int argc,char **argv,char **envp)
{
        ft_env(envp);
        return 0;

}
*/
