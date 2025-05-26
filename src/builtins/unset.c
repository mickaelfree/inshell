/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 21:13:59 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO::
#include "../../includes/inshell.h"


int builtin_unset(char **args, char **envp)
{
        int i;
        i = 1;
        if (!args[1])
                return (1);
        while (envp[i])
        {
                if (!strcmp(envp[i], args[1]))
                {
                        free(envp[i]);
                        envp[i] = envp[i + 1];
                        i++;
                }
                i++;
        }
        return (0);
}
