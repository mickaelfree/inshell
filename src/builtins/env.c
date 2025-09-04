/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:41 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 22:01:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "libft.h"

int builtin_env(char *token, char ***envp)
{
    int     i;
    char    **args;
    char    **ev;
    
    ev = *envp;
    if (!ev)
        return (EXIT_FAILURE);
    if (token && *token)
    {
        args = ft_split(token, ' ');
        if (args && args[0])
        {
            printf("env: too many arguments\n");
            ft_free_split(args);
            return (127);
        }
        if (args)
            ft_free_split(args);
    }
    i = 0;
    while (ev[i])
    {
        printf("%s\n", ev[i]);
        i++;
    }
    return (0);
}
