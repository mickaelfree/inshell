/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:14:31 by zsonie            #+#    #+#             */
/*   Updated: 2025/10/01 00:29:45 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_builtins.h>
#include <ft_enum.h>
#include <ft_structs.h>
#include <ft_utils.h>
#include <mandatoshell.h>
#include <signal.h>
#include <unistd.h>

static int	child_check(t_child_ctx *ctx)
{
	if (ctx->cmd->args && ctx->cmd->args[0])
	{
		if (is_builtin(ctx->cmd->args) == BUILTIN_EXIT)
		{
			destroy_pipeline(ctx->pipeline);
			builtin_exit_child(ctx->head, ctx->cmd, ctx->cmd->args, ctx->envp);
		}
		else if (is_builtin(ctx->cmd->args) != -1)
			return (execute_builtin(ctx->cmd, ctx->envp));
		destroy_pipeline(ctx->pipeline);
		execute(*ctx);
		ft_free_commands(ctx->head);
		ft_free_env(*(ctx->envp));
	}
	return (0);
}

int	execute_child(t_child_ctx *ctx)
{
	int	i;
	int	saved_stdin;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!setup_child_pipes(ctx->index, ctx->pipeline))
		return (1);
	i = 0;
	while (i < ctx->pipeline->pipe_count)
	{
		close(ctx->pipeline->pipes[i][0]);
		close(ctx->pipeline->pipes[i][1]);
		i++;
	}
	saved_stdin = dup(STDIN_FILENO);
	if (!exec_redirections(ctx->cmd, saved_stdin))
	{
		close(saved_stdin);
		return (1);
	}
	close(saved_stdin);
	return (child_check(ctx));
}
