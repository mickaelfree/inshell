/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/27 14:48:19 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO::
#include "../../includes/inshell.h"
int is_valide_export(char **args)
{
        int i;

        i = 0;
        if (!ft_isalpha(args[1][0]))
                return (0);
        while (args[1][i])
        {
                if (!ft_isalnum(args[1][i]) && args[1][i] != '_')
                        return (0);
                i++;
        }
        return (1);
}
int is_no_arg(char **args, char **envp)
{
        int i ;
        i = 0;
        if (!args[1])
        {
                while (envp[i])
                {
                        printf("export %s\n", envp[i]);
                        i++;
                }
                return (1);
        }
        return (0);
}

int builtin_export(char **args, char **envp)
{
        int i;

        i = 1;
        if (is_no_arg(args, envp))
                return (1);
        if(!is_valide_export(args))
        {
                printf("export: `%s':not a valid identifier\n", args[1]);
                return (0);
        }
        while (envp[i])
        {
                if (!strcmp(envp[i], args[1]))
                {
                        free(envp[i]);
                        envp[i] = ft_strdup(args[1]);
                        return (0);
                }
                i++;
        }
        envp[i] = ft_strdup(args[1]);
        envp[i + 1] = NULL;
        return (0);
}
