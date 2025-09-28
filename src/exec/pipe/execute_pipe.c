/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:46:11 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 06:18:35 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "ft_utils.h"
#include "mandatoshell.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	execute_child(t_command *cmd, int index, t_pipeline *pipeline,
		char ***envp)
{
	int	i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (index > 0)
		dup2(pipeline->pipes[index - 1][0], STDIN_FILENO);
	if (index < pipeline->cmd_count - 1)
		dup2(pipeline->pipes[index][1], STDOUT_FILENO);
	i = 0;
	while (i < pipeline->pipe_count)
	{
		close(pipeline->pipes[i][0]);
		close(pipeline->pipes[i][1]);
		i++;
	}
	if (!exec_redirections(cmd))
		return (1);
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args) != -1)
			return (execute_builtin(cmd, envp));
		execute(cmd->args, *envp);
	}
	return (0);
}

static int	handle_fork_error(t_pipeline *pipeline, int failed_index)
{
	int	j;
	int	status;

	perror("fork");
	j = 0;
	while (j < failed_index)
	{
		kill(pipeline->pids[j], SIGTERM);
		j++;
	}
	j = 0;
	while (j < failed_index)
	{
		while (waitpid(pipeline->pids[j], &status, 0) == -1)
		{
			if (errno != EINTR)
				break ;
		}
		j++;
	}
	return (0);
}

static int	fork_all_processes(t_command *cmds, t_pipeline *pipeline,
		char ***envp)
{
	t_command	*cur;
	int			i;
	int			exitcode;

	cur = cmds;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		pipeline->pids[i] = fork();
		if (pipeline->pids[i] == -1)
			return (handle_fork_error(pipeline, i));
		else if (pipeline->pids[i] == 0)
		{
			exitcode = execute_child(cur, i, pipeline, envp);
			ft_free_commands(cmds);
			destroy_pipeline(pipeline);
			ft_free_env(*envp);
			exit(exitcode);
		}
		cur = cur->next;
		i++;
	}
	return (1);
}

static void	wait_all_children(t_pipeline *pipeline)
{
	int	status;
	int	last_exit_status;
	int	sig;
	int	i;

	last_exit_status = 0;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		waitpid(pipeline->pids[i], &status, 0);
		if (i == pipeline->cmd_count - 1)
			last_exit_status = status;
		i++;
	}
	if (WIFSIGNALED(last_exit_status))
	{
		sig = WTERMSIG(last_exit_status);
		g_last_exit_status = 128 + sig;
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}
	else if (WIFEXITED(last_exit_status))
		g_last_exit_status = WEXITSTATUS(last_exit_status);
	else
		g_last_exit_status = 1;
}

void	execute_pipe(t_command *cmds, int cmd_count, char ***envp)
{
	t_pipeline	*pipeline;

	pipeline = create_pipeline(cmd_count);
	if (!pipeline)
	{
		perror("create_pipeline failed");
		g_last_exit_status = 1;
		return ;
	}
	if (pipeline->pipe_count > 0 && !setup_pipes(pipeline))
	{
		destroy_pipeline(pipeline);
		return ;
	}
	if (!fork_all_processes(cmds, pipeline, envp))
	{
		destroy_pipeline(pipeline);
		return ;
	}
	close_parent_pipes(pipeline);
	wait_all_children(pipeline);
	destroy_pipeline(pipeline);
}
