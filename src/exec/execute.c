/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:40:00 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/18 16:20:43 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

static void	handle_command_not_found(char **cmd)
{
	write(STDERR_FILENO, "command not found: ", 19);
	write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
	write(STDERR_FILENO, "\n", 1);
	ft_free(cmd);
	exit(127);
}

static void	check_file_permissions(char *path, char **cmd)
{
	if (access(path, F_OK) == -1)
	{
		ft_free(cmd);
		free(path);
		ft_error("no such file or directory");
	}
	if (access(path, X_OK) == -1)
	{
		ft_free(cmd);
		free(path);
		write(STDERR_FILENO, "permission denied\n", 18);
		exit(126);
	}
}

static void	execute_command(char *path, char **cmd, char **env)
{
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_free(cmd);
		ft_error("execve error");
	}
}

void	execute(char **av, char **env)
{
	char	*path;

	// char	**cmd;
	//(void)cmd;
	// cmd = ft_split(av, ' ');
	// if (cmd == NULL)
	// ft_error("malloc error");
	path = find_path(*av, env);
	if (path == NULL)
		handle_command_not_found(av);
	check_file_permissions(path, av);
	execute_command(path, av, env);
}
