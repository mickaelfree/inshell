/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 19:11:20 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO::
#include "../../includes/inshell.h"

int is_valid_identifier(char *str)
{
        int i;

        i = 0;
        if (!ft_isalpha(str[i]) && str[i] != '_')
                return (0);
        i++;
        while (str[i])
        {
                if (!ft_isalnum(str[i]) && str[i] != '_')
                        return (0);
                i++;
        }
        return (1);
}

int builtin_unset(char **args, char **envp)
{
        int i;
        i = 1;
        if (!args[1])
                return (1);
        while (args[i])
        {
                if (!is_valid_identifier(args[i]))
                {
                        printf("unset: %s: not a valid identifier\n", args[i]);
                        return (1);
                }
                i++;
        }
        printf("unset: %s:valid identifier\n", args[i]);
        i = 0;
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
