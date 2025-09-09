/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:20:51 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/07 02:26:07 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include <unistd.h>

static int	count_pipeline(t_command *cmds)
{
	int			count;
	t_command	*cur;

	count = 0;
	cur = cmds;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

static void	handle_redirections(t_command *cmd)
{
	t_redirection	*redir;
	int				fd;
	int				flags;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			char *temp_file = process_heredoc(redir->filename);
			if (!temp_file)
				exit(1);
			fd = open(temp_file, O_RDONLY);
			if (fd == -1)
			{
				perror("open heredoc");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			unlink(temp_file);
			free(temp_file);
		}
		else if (redir->type == TOKEN_REDIR_IN)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd == -1)
			{
				perror(redir->filename);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
		{
			flags = O_WRONLY | O_CREAT | (redir->append_mode ? O_APPEND : O_TRUNC);
			fd = open(redir->filename, flags, 0644);
			if (fd == -1)
			{
				perror(redir->filename);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}

static t_pipeline	*create_pipeline(int cmd_count)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->cmd_count = cmd_count;
	pipeline->pipe_count = cmd_count - 1;
	pipeline->pids = malloc(cmd_count * sizeof(pid_t));
	pipeline->pipes = NULL;
	if (cmd_count > 1)
		pipeline->pipes = malloc(pipeline->pipe_count * sizeof(int[2]));
	if (!pipeline->pids || (cmd_count > 1 && !pipeline->pipes))
	{
		free(pipeline->pids);
		free(pipeline->pipes);
		free(pipeline);
		return (NULL);
	}
	return (pipeline);
}

static void	destroy_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free(pipeline->pids);
	free(pipeline->pipes);
	free(pipeline);
}

static int	setup_pipes(t_pipeline *pipeline)
{
	int	i;
	int	j;

	i = 0;
	while (i < pipeline->pipe_count)
	{
		if (pipe(pipeline->pipes[i]) == -1)
		{
			j = 0;
			while (j < i)
			{
				close(pipeline->pipes[j][0]);
				close(pipeline->pipes[j][1]);
				j++;
			}
			perror("pipe");
			g_last_exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	execute_child(t_command *cmd, int index, t_pipeline *pipeline,
		char ***envp)
{
	int	i;

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
	handle_redirections(cmd);
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args) != -1)
			exit(execute_builtin(cmd->args, envp));
		execute(cmd->args, *envp);
	}
	exit(0);
}

static int	fork_all_processes(t_command *cmds, t_pipeline *pipeline,
		char ***envp)
{
	t_command	*cur;
	int			i;
	int			j;

	cur = cmds;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		pipeline->pids[i] = fork();
		if (pipeline->pids[i] == -1)
		{
			perror("fork");
			j = 0;
			while (j < i)
			{
				kill(pipeline->pids[j], SIGTERM);
				j++;
			}
			return (0);
		}
		else if (pipeline->pids[i] == 0)
		{
			execute_child(cur, i, pipeline, envp);
		}
		cur = cur->next;
		i++;
	}
	return (1);
}

static void	execute_builtin_in_parent(t_command *cmd, char ***envp)
{
	int	saved_stdin;
	int	saved_stdout;
	int	builtin_ret;

	saved_stdin = -1;
	saved_stdout = -1;
	if (cmd->input_file || cmd->output_file)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
	}
	handle_redirections(cmd);
	builtin_ret = execute_builtin(cmd->args, envp);
	g_last_exit_status = builtin_ret;
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

static void	close_parent_pipes(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->pipe_count)
	{
		close(pipeline->pipes[i][0]);
		close(pipeline->pipes[i][1]);
		i++;
	}
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
		// Dernier processus détermine le status global
		if (i == pipeline->cmd_count - 1)
			last_exit_status = status;
		i++;
	}
	// Interpréter status
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
static void	execute_pipeline(t_command *cmds, int cmd_count, char ***envp)
{
	t_pipeline	*pipeline;

	pipeline = create_pipeline(cmd_count);
	if (!pipeline)
	{
		perror("create_pipeline failed");
		g_last_exit_status = 1;
		return ;
	}
	// Setup pipes si nécessaire
	if (pipeline->pipe_count > 0 && !setup_pipes(pipeline))
	{
		destroy_pipeline(pipeline);
		return ;
	}
	// Fork tous les processus
	if (!fork_all_processes(cmds, pipeline, envp))
	{
		destroy_pipeline(pipeline);
		return ;
	}
	// Parent : fermer pipes et attendre
	close_parent_pipes(pipeline);
	wait_all_children(pipeline);
	destroy_pipeline(pipeline);
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
	execute_pipeline(cmds, cmd_count, envp);
}
