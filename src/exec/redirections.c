/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:28:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/22 17:20:02 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

#define NB_REDIRS_FUNC 3


static int rd_in(t_redirection *r)
{
	int fd;

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

static int rd_out(t_redirection *r)
{
	int fd;
	int flags;

	flags = O_WRONLY | O_CREAT | (r->append_mode ? O_APPEND : O_TRUNC);
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

static int rd_heredoc(t_redirection *r)
{
	char *tmp;
	int   fd;

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
		free(tmp);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		unlink(tmp);
		free(tmp);
		return (0);
	}
	close(fd);
	unlink(tmp);
	free(tmp);
	return (1);
}



static void init_redir_table(t_redir_entry *func)
{

	func[0] = (t_redir_entry){TOKEN_HEREDOC,   rd_heredoc};
	func[1] = (t_redir_entry){TOKEN_REDIR_IN,  rd_in};
	func[2] = (t_redir_entry){TOKEN_REDIR_OUT, rd_out};
	/* NB: TOKEN_APPEND est traité par rd_out via r->append_mode */
}

/* ---------- dispatcher “lookup” ---------- */

static int apply_redirection(t_redirection *r)
{
	t_redir_entry func[NB_REDIRS_FUNC];
	int           i;

	init_redir_table(func);
	if (r->type == TOKEN_APPEND)
		r->append_mode = 1;
	i = 0;
	while (i < NB_REDIRS_FUNC)
	{
		if (func[i].type == r->type
		 || (r->type == TOKEN_APPEND && func[i].type == TOKEN_REDIR_OUT))
		{
			return (func[i].fn(r));
		}
		i++;
	}
	return (1);
}

int handle_redirections(t_command *cmd)
{
	t_redirection *rd;

	rd = cmd->redirections;
	while (rd)
	{
		if (!apply_redirection(rd))
			return (0);
		rd = rd->next;
	}
	return (1);
}
