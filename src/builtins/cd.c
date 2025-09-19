/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:23 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/20 01:41:11 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"

static char	*get_target_directory(char **args, int *print_pwd, char **envp)
{
	char	*home;
	char	*old;

	*print_pwd = 0;
	if (!args[1])
	{
		home = get_env_value("HOME", envp);
		if (!home || !*home)
			return (cd_err(" HOME not set\n", 1));
		return (home);
	}
	if (!ft_strncmp(args[1], "-", 1))
	{
		old = get_env_value("OLDPWD", envp);
		if (!old || !*old)
			return (cd_err(" OLDPWD not set\n", 1));
		*print_pwd = 1;
		return (old);
	}
	return (args[1]);
}

static int	change_and_get_paths(char *target_dir, char **old_pwd,
		char **new_pwd)
{
	*old_pwd = getcwd(NULL, 0);
	if (!*old_pwd)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (chdir(target_dir) == -1)
	{
		perror("cd");
		free(*old_pwd);
		*old_pwd = NULL;
		return (EXIT_FAILURE);
	}
	*new_pwd = getcwd(NULL, 0);
	if (!*new_pwd)
	{
		perror("cd");
		chdir(*old_pwd);
		free(*old_pwd);
		*old_pwd = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	free_paths_and_vars(char *old_pwd, char *new_pwd, char *oldpwd_var,
		char *pwd_var)
{
	free(oldpwd_var);
	free(pwd_var);
	free(old_pwd);
	free(new_pwd);
}

static int	update_directory(char *target_dir, int print_pwd, char ***envp)
{
	char	*oldpwd;
	char	*pwd;
	char	*oldpwd_var;
	char	*pwd_var;

	if (change_and_get_paths(target_dir, &oldpwd, &pwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	pwd_var = ft_strjoin("PWD=", pwd);
	if (!oldpwd_var || !pwd_var)
	{
		free_paths_and_vars(oldpwd, pwd, oldpwd_var, pwd_var);
		return (EXIT_FAILURE);
	}
	update_env_var(envp, oldpwd_var);
	update_env_var(envp, pwd_var);
	if (print_pwd)
		printf("%s\n", pwd);
	free_paths_and_vars(oldpwd, pwd, oldpwd_var, pwd_var);
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **args, char ***envp)
{
	int		print_pwd;
	char	*target_dir;

	if (args[1] && args[2])
	{
		cd_err(" too many arguments\n", 2);
		return (g_last_exit_status);
	}
	target_dir = get_target_directory(args, &print_pwd, *envp);
	if (!target_dir)
		return (g_last_exit_status);
	return (update_directory(target_dir, print_pwd, envp));
}
