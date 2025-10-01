/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:01:51 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 20:13:48 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft_strings.h>
#include <ft_write.h>
#include <mandatoshell.h>
#include <stdlib.h>
#include <unistd.h>

void	error_exit(void)
{
	if (errno == 2 || errno == 14)
	{
		if (errno == 2)
			ft_putstr_fd(" No such file or directory\n", 2);
		if (errno == 14)
			ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	if (errno == 13)
	{
		ft_putstr_fd("Permission denied\n", 2);
		exit(126);
	}
	exit(1);
}

void	handle_error_ctx(char *patch, int status, t_child_ctx ctx)
{
	if (status == 127)
	{
		write(STDERR_FILENO, ctx.cmd->args[0], ft_strlen(ctx.cmd->args[0]));
		write(2, ": No such file or directory\n",
			sizeof(": No such file or directory\n"));
	}
	else if (ft_strlen((const char *)ctx.cmd->args[0]) == 0)
	{
		write(STDERR_FILENO, " ", 1);
		write(2, ": command not found\n", sizeof(": command not found\n"));
		status = 127;
	}
	else if (ctx.cmd->args[0][0] == '/')
	{
		write(STDERR_FILENO, ctx.cmd->args[0], ft_strlen(ctx.cmd->args[0]));
		write(2, ": Is a directory\n", sizeof(": Is a directory\n"));
	}
	else if (status == 126)
	{
		write(STDERR_FILENO, ctx.cmd->args[0], ft_strlen(ctx.cmd->args[0]));
		write(2, ": Permission denied\n", sizeof(": Permission denied\n"));
	}
	cleanup_path_and_ctx(patch, ctx, status);
}

void	ft_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	if (ft_strnstr(msg, " No such file or directory", 27))
	{
		g_last_exit_status = 127;
		exit(127);
	}
	if (ft_strnstr(msg, "Permission denied", 18))
	{
		g_last_exit_status = 126;
		exit(126);
	}
	g_last_exit_status = 1;
	exit(1);
}

void	export_error(char *arg)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	g_last_exit_status = 1;
}
