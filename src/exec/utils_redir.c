/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:37:55 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/22 18:51:40 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

int	rd_in(t_redirection *r)
{
	int	fd;

	fd = open(r->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(r->filename);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	rd_out(t_redirection *r)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (r->append_mode)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(r->filename, flags, 0644);
	if (fd < 0)
	{
		perror(r->filename);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	cleanup_heredoc(char *tmp, int fd, int success)
{
	if (fd >= 0)
		close(fd);
	if (tmp)
	{
		unlink(tmp);
		free(tmp);
	}
	return (success);
}

int	rd_heredoc(t_redirection *r)
{
	char	*tmp;
	int		fd;

	tmp = process_heredoc(r->filename);
	if (!tmp)
	{
		perror("heredoc");
		return (0);
	}
	fd = open(tmp, O_RDONLY);
	if (fd < 0)
	{
		perror(tmp);
		return (cleanup_heredoc(tmp, -1, 0));
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (cleanup_heredoc(tmp, fd, 0));
	}
	return (cleanup_heredoc(tmp, fd, 1));
}

void	init_redir_table(t_redir_entry *func)
{
	func[0] = (t_redir_entry){TOKEN_HEREDOC, rd_heredoc};
	func[1] = (t_redir_entry){TOKEN_REDIR_IN, rd_in};
	func[2] = (t_redir_entry){TOKEN_REDIR_OUT, rd_out};
}
