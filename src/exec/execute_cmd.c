/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:20:51 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/04 18:27:06 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

/*on cree les processus enfants
pour le premier
parent
[] while(n)    [stdin] ||=fork()-> cmd ||          || pipe
||=fork()-> cmd
||          || pipe
||=fork()-> cmd
||          || pipe
			[stdout]
*/
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

static int one_cmd(t_command *cmd, char ***envp)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        handle_redirections(cmd);
        if (cmd->arg_count > 0 && !is_builtin(cmd->args, envp))
            execute(cmd->args, *envp);
        exit(0);
    }
    waitpid(pid, &status, 0);
    return 0;
}
static int pipe_error(int (*pipes)[2], pid_t *pids, int cmd_count)
{
        int i;
        i = 0;
        while (i < cmd_count - 1)
        {
                close(pipes[i][0]);
                close(pipes[i][1]);
                i++;
        }
	perror("pipe");
        free(pipes);
        free(pids);
        return (1);

}
static int fork_error(int (*pipes)[2], pid_t *pids, int cmd_count, int i)
{
        int j;
        j = 0;
        while (j < i)
        {
                kill(pids[j], SIGTERM);
                j++;
        }
        j = 0;
        while (j < cmd_count - 1)
        {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
        }
        perror("fork");
        free(pipes);
        free(pids);
        return (1);
}
void	execute_cmd(t_command *cmds, char ***envp)
{
	int			cmd_count;
	int			j;
	int			(*pipes)[2];
	 pid_t		*pids;
	t_command	*cur;
	int			i;
	cmd_count = count_pipeline(cmds);
	if (cmd_count == 0)
		return ;
	cur = cmds;
        if (cmd_count == 1)
        {
                one_cmd(cmds, envp);
                return ;
        }
        pipes = malloc((cmd_count - 1) * sizeof(int[2]));
        pids = malloc(cmd_count * sizeof(pid_t));
        if (!pids || (cmd_count > 1 && !pipes))
        {
			perror("fail malloc");
			return ;
        }
	i = 0;

	// Créer pipes
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
                       pipe_error(pipes, pids, cmd_count);
			return ;
		}
		i++;
	}
	// Fork pour chaque cmd
	i = 0;
	while (cur)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
                        fork_error(pipes, pids, cmd_count, i);
			return ;
		}
		else if (pids[i] == 0) // Child
		{
			// Gérer pipes
			if (i > 0) // Input from previous pipe
			{
				dup2(pipes[i - 1][0], STDIN_FILENO);
				close(pipes[i - 1][0]);
				close(pipes[i - 1][1]);
			}
			if (i < cmd_count - 1) // Output to next pipe
			{
				dup2(pipes[i][1], STDOUT_FILENO);
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
			// Fermer tous les autres pipes
			j = 0;
			while (j < cmd_count - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			// Gérer redirs (overwrites pipes si présent)
			handle_redirections(cur);
			// Exécuter
			if (cur->arg_count > 0 && !is_builtin(cur->args,envp))
				execute(cur->args, *envp); // Ton execute pour externe
			exit(0);                      // Si rien
		}
		cur = cur->next;
		i++;
	}
	// Parent ferme pipes
	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	// Wait enfants
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
        free(pipes);
        free(pids);
}
