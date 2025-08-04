/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:23 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/04 18:09:44 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"

static char	*get_target_directory(char **args, int *print_pwd)
{
	*print_pwd = 0;
	if (args[1] && args[2]) 
        {
		printf("cd: too many arguments");
		return (NULL);
	}
	if (!args[1]) 
        {
		char *home = getenv("HOME");
		if (!home || !*home) 
                {
			printf("cd: HOME not set");
			return (NULL);
		}
		return (home);
	}
	if (!strcmp(args[1], "-")) 
        {
		char *old = getenv("OLDPWD");
		if (!old || !*old) {
			printf("cd: OLDPWD not set");
			return (NULL);
		}
		*print_pwd = 1;
		return (old);
	}
	return (args[1]);
}

static int	update_directory(char *target_dir, int print_pwd)
{
	char	*oldpwd = getcwd(NULL, 0);
	if (!oldpwd) 
        {
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (chdir(target_dir) == -1)
        {
		perror("cd");
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	char	*pwd = getcwd(NULL, 0);
	if (!pwd) 
        {
		perror("cd");
		free(oldpwd);
		chdir(oldpwd);
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", pwd, 1);
	if (print_pwd)
		printf("%s\n", pwd);
	free(oldpwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
int	builtin_cd(char **args, char ***envp)
{
        int print_pwd;
	char	*target_dir;

	(void)envp;
	target_dir = get_target_directory(args,&print_pwd);
        if (!target_dir)
		return (EXIT_FAILURE);
	return (update_directory(target_dir, print_pwd));
}
