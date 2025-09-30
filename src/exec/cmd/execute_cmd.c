/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:20:51 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/30 04:57:49 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "ft_builtins.h"
#include "ft_signal.h"
#include "signal.h"
#include "unistd.h"

static void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

static void	execute_builtin_in_parent(t_command *cmd, char ***envp)
{
	int	saved_stdin;
	int	saved_stdout;
	int	builtin_ret;

	saved_stdin = -1;
	saved_stdout = -1;
	if (cmd->redirections)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
	}
	if (!exec_redirections(cmd, saved_stdin))
	{
		g_last_exit_status = 1;
		restore_std_fds(saved_stdin, saved_stdout);
		return ;
	}
	builtin_ret = execute_builtin(cmd, envp);
	g_last_exit_status = builtin_ret;
	restore_std_fds(saved_stdin, saved_stdout);
}

void	execute_cmd(t_command *cmds, char ***envp)
{
	int	cmd_count;

	cmd_count = count_pipeline(cmds);
	if (cmd_count == 0)
		return ;
	if (cmd_count == 1 && cmds->args && cmds->args[0])
	{
		if (is_builtin(cmds->args) != -1)
		{
			execute_builtin_in_parent(cmds, envp);
			return ;
		}
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	execute_pipe(cmds, cmd_count, envp);
	signal(SIGINT, ft_handle_sig);
	signal(SIGQUIT, ft_handle_sig);
}
