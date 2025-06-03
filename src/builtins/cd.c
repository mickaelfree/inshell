/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:23 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/03 23:49:29 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO::
#include "../../includes/inshell.h"

int	builtin_cd(char **args,char **envp)
{
        (void)envp;
        char *oldpwd;
        char *pwd;

        if (!args[1])
        {
                chdir(getenv("HOME"));
                return (EXIT_SUCCESS);
        }
        if (!strcmp(args[1], "-"))
        {
                chdir(getenv("OLDPWD"));
                return (EXIT_SUCCESS);
        }
        oldpwd = getcwd(NULL, 0);
        if (!oldpwd)
                return (EXIT_FAILURE);
        if (chdir(args[1]) == -1)
        {
                free(oldpwd);
                return (EXIT_FAILURE);
        }
        pwd = getcwd(NULL, 0);
        if (!pwd)
        {
                free(oldpwd);
                return (EXIT_FAILURE);
        }
        setenv("OLDPWD", oldpwd, 1);
        setenv("PWD", pwd, 1);
        free(oldpwd);
        free(pwd);
        return (EXIT_SUCCESS);
}
