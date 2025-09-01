/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:20:51 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/01 00:06:36 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include <unistd.h>

int					status = 0;

static void	handle_redirections(t_command *cmd)
{
	int	fd;
	int	flags;

	if (cmd->heredoc_delim)
	{
		cmd->input_file = process_heredoc(cmd->heredoc_delim); // Crée tmp file
		if (!cmd->input_file)
			exit(1); // Erreur
	}
	if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd == -1)
		{
			perror("open input");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (cmd->heredoc_delim) // Supprime tmp après open
			unlink(cmd->input_file);
	}
	if (cmd->output_file)
	{
		flags = O_WRONLY | O_CREAT | (cmd->append_mode ? O_APPEND : O_TRUNC);
		fd = open(cmd->output_file, flags, 0644);
		if (fd == -1)
		{
			perror("open output");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
//
// static int	one_cmd(t_command *cmd, char ***envp)
// {
// 	pid_t	pid;
// 	int		status;
//
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
// 		handle_redirections(cmd);
// 		if (cmd->arg_count > 0 && is_builtin(cmd->args, envp) == -1)
// 			execute(cmd->args, *envp);
// 		exit(0);
// 	}
// 	waitpid(pid, &status, 0);
// 	g_last_exit_status = WEXITSTATUS(status);
// 	return (0);
// }
// static int	pipe_error(int (*pipes)[2], pid_t *pids, int cmd_count)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i < cmd_count - 1)
// 	{
// 		close(pipes[i][0]);
// 		close(pipes[i][1]);
// 		i++;
// 	}
// 	perror("pipe");
// 	free(pipes);
// 	free(pids);
// 	return (1);
// }
// static int	fork_error(int (*pipes)[2], pid_t *pids, int cmd_count, int i)
// {
// 	int	j;
//
// 	j = 0;
// 	while (j < i)
// 	{
// 		kill(pids[j], SIGTERM);
// 		j++;
// 	}
// 	j = 0;
// 	while (j < cmd_count - 1)
// 	{
// 		close(pipes[j][0]);
// 		close(pipes[j][1]);
// 		j++;
// 	}
// 	perror("fork");
// 	free(pipes);
// 	free(pids);
// 	return (1);
// }
// void	execute_cmd(t_command *cmds, char ***envp)
// {
// 	int			cmd_count;
// 	int			j;
// 	pid_t		*pids;
// 	t_command	*cur;
// 	int			i;
// 	int			status;
//         void (*old_int)(int);
//         void (*old_quit)(int);
//
// 	int(*pipes)[2];
// 	cmd_count = count_pipeline(cmds);
// 	if (cmd_count == 0)
// 		return ;
// 	cur = cmds;
// 	if (cmd_count == 1)
// 	{
// 		one_cmd(cmds, envp);
// 		return ;
// 	}
// 	pipes = malloc((cmd_count - 1) * sizeof(int[2]));
// 	pids = malloc(cmd_count * sizeof(pid_t));
// 	if (!pids || (cmd_count > 1 && !pipes))
// 	{
// 		perror("fail malloc");
// 		return ;
// 	}
// 	i = 0;
//         old_int = signal(SIGINT, SIG_DFL);
//         old_quit = signal(SIGQUIT, SIG_DFL);
// 	// Créer pipes
// 	while (i < cmd_count - 1)
// 	{
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			pipe_error(pipes, pids, cmd_count);
//                         g_last_exit_status = 1;
//                         signal(SIGINT, old_int);
//                         signal(SIGQUIT, old_quit);
// 			return ;
// 		}
// 		i++;
// 	}
// 	// Fork pour chaque cmd
// 	i = 0;
// 	while (cur)
// 	{
// 		pids[i] = fork();
// 		if (pids[i] == -1)
// 		{
// 			fork_error(pipes, pids, cmd_count, i);
// 			return ;
// 		}
// 		else if (pids[i] == 0) // Child
// 		{
//                         signal(SIGINT, old_int);
//                         signal(SIGQUIT, old_quit);
// 			// Gérer pipes
// 			if (i > 0) // Input from previous pipe
// 			{
// 				dup2(pipes[i - 1][0], STDIN_FILENO);
// 				close(pipes[i - 1][0]);
// 				close(pipes[i - 1][1]);
// 			}
// 			if (i < cmd_count - 1) // Output to next pipe
// 			{
// 				dup2(pipes[i][1], STDOUT_FILENO);
// 				close(pipes[i][0]);
// 				close(pipes[i][1]);
// 			}
// 			// Fermer tous les autres pipes
// 			j = 0;
// 			while (j < cmd_count - 1)
// 			{
// 				close(pipes[j][0]);
// 				close(pipes[j][1]);
// 				j++;
// 			}
// 			// Gérer redirs (overwrites pipes si présent)
// 			handle_redirections(cur);
// 			// Exécuter
// 			if (cur->arg_count > 0 )
//                         {
//                                 int builtin_status = is_builtin(cur->args,
//		envp);
//                                 if (builtin_status != -1)
//                                         exit(builtin_status);
// 				execute(cur->args, *envp); // Ton execute pour externe
//                         }
// 			exit(0);                       // Si rien
// 		}
// 		cur = cur->next;
// 		i++;
// 	}
// 	// Parent ferme pipes
// 	i = 0;
// 	while (i < cmd_count - 1)
// 	{
// 		close(pipes[i][0]);
// 		close(pipes[i][1]);
// 		i++;
// 	}
// 	// Wait enfants
// 	i = 0;
// 	while (i < cmd_count)
// 	{
// 		waitpid(pids[i], &status, 0);
//                 if(i == cmd_count - 1)
//                 {
//                         if(WIFSIGNALED(status))
//                         {
//                                 int sig = WTERMSIG(status);
//                                         g_last_exit_status = 128 + sig;
//                                 if(sig == SIGQUIT)
//                                         write(STDERR_FILENO,
//	"Quit (core dumped)\n", 19);
//                         }
//                         else if (WIFEXITED(status))
//                                 g_last_exit_status = WEXITSTATUS(status);
//                         else
//                                 g_last_exit_status = 1;
//                 }
// 		i++;
// 	}
// 	free(pipes);
// 	free(pids);

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
		if (is_builtin(cmd->args, envp) != -1)
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
void	execute_cmd(t_command *cmds, char ***envp)
{
	int	cmd_count;

	cmd_count = count_pipeline(cmds);
	if (cmd_count == 0)
		return ;
	if (cmd_count == 1 && cmds->args && cmds->args[0])
	{
		if (is_builtin(cmds->args, envp) != -1)
		{
			execute_builtin_in_parent(cmds, envp);
			return ;
		}
	}
	execute_pipeline(cmds, cmd_count, envp);
}
