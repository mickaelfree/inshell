/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:40:00 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/22 18:12:02 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

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
	errno = 0;
	if (access(path, F_OK) == -1)
	{
		ft_free(cmd);
		free(path);
		error_exit();
	}
	if (access(path, X_OK) == -1)
	{
		ft_free(cmd);
		free(path);
		error_exit();
	}
}

static void	execute_command(char *path, char **cmd, char **env)
{
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_free(cmd);
		if (errno == ENOENT)
		{
			write(STDERR_FILENO, "command not found\n", 18);
			g_last_exit_status = 127;
			exit(127);
		}
		else if (errno == EACCES)
		{
			write(STDERR_FILENO, " Permission denied\n", 19);
			g_last_exit_status = 126;
			exit(126);
		}
		else
		{
			perror("execve");
			exit(1);
		}
	}
}

void	execute(char **av, char **env)
{
	char	*path;

	path = find_path(*av, env);
	if (path == NULL)
		handle_command_not_found(av);
	check_file_permissions(path, av);
	execute_command(path, av, env);
}
