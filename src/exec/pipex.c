/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:46:17 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/04 22:13:12 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

static void	clean_exit(char *msg, int fd1, int fd2)
{
	if (fd1 > 2)
		close(fd1);
	if (fd2 > 2)
		close(fd2);
	ft_error(msg);
}

void	child_process(char **av, char **env, int *fd)
{
	int	filein;

	close(fd[0]);
	filein = open(av[1], O_RDONLY);
	if (filein == -1)
		clean_exit(strerror(errno), fd[1], -1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		clean_exit("dup2 error", fd[1], filein);
	if (dup2(filein, STDIN_FILENO) == -1)
		clean_exit("dup2 error", fd[1], filein);
	if (close(filein) == -1 || close(fd[1]) == -1)
		ft_error("close error");
	execute(av[2], env);
	ft_error("child process error");
}

void	child_process2(char **av, char **env, int *fd)
{
	int	fileout;

	close(fd[1]);
	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		clean_exit(strerror(errno), fd[0], -1);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		clean_exit("dup2 error", fd[0], fileout);
	if (dup2(fileout, STDOUT_FILENO) == -1)
		clean_exit("dup2 error", fd[0], fileout);
	if (close(fileout) == -1 || close(fd[0]) == -1)
		ft_error("close error");
	execute(av[3], env);
	ft_error("child process error");
}

void	create_processes(char **av, char **env, int *fd, int *status)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;

	pid1 = fork();
	if (pid1 == -1)
		clean_exit("fork failed", fd[0], fd[1]);
	if (pid1 == 0)
		child_process(av, env, fd);
	pid2 = fork();
	if (pid2 == -1)
		clean_exit("fork failed", fd[0], fd[1]);
	if (pid2 == 0)
		child_process2(av, env, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, status, 0);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	status;

	if (ac != 5)
		ft_error("Invalid number of arguments");
	if (pipe(fd) == -1)
		ft_error("pipe error");
	create_processes(av, env, fd, &status);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	else
		status = 1;
	return (status);
}
