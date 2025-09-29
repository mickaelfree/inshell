/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:40:00 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 20:01:52 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft_strings.h>
#include <ft_structs.h>
#include <ft_utils.h>
#include <mandatoshell.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	cleanup_path_and_ctx(char *path, t_child_ctx ctx, int exit_code)
{
	if (path)
		free(path);
	if (ctx.head)
		ft_free_commands(ctx.head);
	if (*(ctx.envp))
		ft_free_env(*(ctx.envp));
	exit(exit_code);
}

static void	handle_command_not_found(t_child_ctx ctx)
{
	write(STDERR_FILENO, ctx.cmd->args[0], ft_strlen(ctx.cmd->args[0]));
	write(STDERR_FILENO, ": command not found", 19);
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
		if (errno == ENOENT || ctx.cmd->args[0][0] == '.')
			handle_command_not_found(ctx);
		else if (errno == EACCES)
			handle_error_ctx(path, 126, ctx);
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

	path = find_path(ctx.cmd->args[0], *(ctx.envp), ctx);
	if (path == NULL)
		handle_command_not_found(ctx);
	check_file_permissions(path, ctx);
	execute_command(path, ctx);
}
