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

static char *get_target_directory(char **args)
{
    if (!args[1])
        return getenv("HOME");
    else if (!strcmp(args[1], "-"))
        return getenv("OLDPWD");
    else
        return args[1];
}

static int update_directory(char *target_dir)
{
    char *oldpwd;
    char *pwd;
    if (!(oldpwd = getcwd(NULL, 0)))
        return (EXIT_FAILURE);
    if (chdir(target_dir) == -1) {
        free(oldpwd);
        return (EXIT_FAILURE);
    }
    if (!(pwd = getcwd(NULL, 0))) {
        free(oldpwd);
        return (EXIT_FAILURE);
    }
    setenv("OLDPWD", oldpwd, 1);
    setenv("PWD", pwd, 1);
    free(oldpwd);
    free(pwd);
    return (EXIT_SUCCESS);
}

int builtin_cd(char **args, char **envp)
{
    (void)envp;
    char *target_dir;
    target_dir = get_target_directory(args);
    return update_directory(target_dir);
}
