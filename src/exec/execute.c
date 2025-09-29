/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:40:00 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 06:33:18 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "ft_structs.h"
#include "ft_utils.h"
#include "libft.h"
#include "mandatoshell.h"
#include "stdio.h"
#include <unistd.h>

static void	cleanup_path_and_ctx(char *path, t_child_ctx ctx, int exit_code)
{
	if (path)
		free(path);
	if (ctx.cmd->args)
		ft_free(ctx.cmd->args);
	if (ctx.index > 0)
		close(STDIN_FILENO);
	if (ctx.index < ctx.pipeline->cmd_count - 1)
		close(STDOUT_FILENO);
	if (ctx.head)
		ft_free_commands(ctx.head);
	if (*(ctx.envp))
		ft_free_env(*(ctx.envp));
	exit(exit_code);
}

static void	handle_command_not_found(t_child_ctx ctx)
{
	write(STDERR_FILENO, "command not found: ", 19);
	write(STDERR_FILENO, ctx.cmd->args[0], ft_strlen(ctx.cmd->args[0]));
	write(STDERR_FILENO, "\n", 1);
	cleanup_path_and_ctx(NULL, ctx, 127);
}

static void	check_file_permissions(char *path, t_child_ctx ctx)
{
	errno = 0;
	if (access(path, F_OK) == -1)
		cleanup_path_and_ctx(path, ctx, 127);
	if (access(path, X_OK) == -1)
		cleanup_path_and_ctx(path, ctx, 126);
}

static void	execute_command(char *path, t_child_ctx ctx)
{
	if (execve(path, ctx.cmd->args, *(ctx.envp)) == -1)
	{
		if (errno == ENOENT)
		{
			write(STDERR_FILENO, "command not found\n", 18);
			cleanup_path_and_ctx(path, ctx, 127);
		}
		else if (errno == EACCES)
		{
			write(STDERR_FILENO, " Permission denied\n", 19);
			cleanup_path_and_ctx(path, ctx, 126);
		}
		else
		{
			perror("execve");
			cleanup_path_and_ctx(path, ctx, 1);
		}
	}
}

void	execute(t_child_ctx ctx)
{
	char	*path;

	path = find_path(ctx.cmd->args[0], *(ctx.envp));
	if (path == NULL)
		handle_command_not_found(ctx);
	check_file_permissions(path, ctx);
	execute_command(path, ctx);
}
