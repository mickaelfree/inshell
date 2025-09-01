/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:23 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/19 17:51:59 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"

static char	*get_target_directory(char **args, int *print_pwd, char **envp)
{
	char	*home;
	char	*old;

	*print_pwd = 0;
	if (args[1] && args[2])
	{
                write(STDERR_FILENO, " too many arguments\n", 19);
                g_last_exit_status = 1;
		return (NULL);
	}
	if (!args[1])
	{
		home = get_env_value("HOME", envp);
		if (!home || !*home)
		{
                        
                        write(STDERR_FILENO, " HOME not set\n", 14);
                        g_last_exit_status = 1;
			return (NULL);
		}
		return (home);
	}
	if (!strcmp(args[1], "-"))
	{
		old = get_env_value("OLDPWD", envp);
		if (!old || !*old)
		{
                        write(STDERR_FILENO, " OLDPWD not set\n", 16);
                        g_last_exit_status = 1;
			return (NULL);
		}
		*print_pwd = 1;
		return (old);
	}
	return (args[1]);
}

static int	update_directory(char *target_dir, int print_pwd, char ***envp)
{
	char	*oldpwd;
	char	*pwd;
	char	*oldpwd_var;
	char	*pwd_var;

	oldpwd = getcwd(NULL, 0);
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
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("cd");
		chdir(oldpwd);
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	pwd_var = ft_strjoin("PWD=", pwd);
	if (!oldpwd_var || !pwd_var)
	{
		free(oldpwd);
		free(pwd);
		free(oldpwd_var);
		free(pwd_var);
		return (EXIT_FAILURE);
	}
	update_env_var(envp, oldpwd_var);
	update_env_var(envp, pwd_var);
	if (print_pwd)
		printf("%s\n", pwd);
	free(oldpwd);
	free(pwd);
	free(oldpwd_var);
	free(pwd_var);
	return (EXIT_SUCCESS);
}
int	builtin_cd(char **args, char ***envp)
{
	int		print_pwd;
	char	*target_dir;

	target_dir = get_target_directory(args, &print_pwd, *envp);
	if (!target_dir)
		return (EXIT_FAILURE);
	return (update_directory(target_dir, print_pwd, envp));
}
