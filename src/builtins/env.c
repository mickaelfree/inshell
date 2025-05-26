/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:41 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 18:42:44 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO::

#include "../../includes/inshell.h"

int builtin_env(char **args, char **envp)
{
        int i;

        i = 0;
        if (args[1])
                return (1);
        while (envp[i])
                printf("%s\n", envp[i++]);
        return (0);
}
