/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 22:02:57 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/23 22:10:48 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

static int	add_redirection_to_list(t_command *cmd, t_redirection *new_redir)
{
	t_redirection	*current;

	if (!cmd || !new_redir)
		return (0);
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	return (1);
}

static t_redirection	*create_redirection(int type, char *filename)
{
	t_redirection	*new_redir;

	if (!filename)
		return (NULL);
	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
	{
		write(STDERR_FILENO, "malloc error\n", 13);
		return (NULL);
	}
	new_redir->type = type;
	new_redir->filename = filename;
	new_redir->append_mode = (type == TOKEN_APPEND);
	new_redir->next = NULL;
	return (new_redir);
}

int	create_and_add_redirection(t_command *cmd, int type, char *filename)
{
	t_redirection	*new_redir;

	new_redir = create_redirection(type, filename);
	if (!new_redir)
		return (0);
	return (add_redirection_to_list(cmd, new_redir));
}
