/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:50:13 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 19:35:25 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

void	free_token_list(t_pre_token *head)
{
	t_pre_token	*current;
	t_pre_token	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_args_and_redir(t_command *current)
{
	t_redirection	*redir;
	t_redirection	*next_redir;
	int i;

	if (current->args)
	{
		i = 0;
		while (i < current->arg_count)
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
	}
	redir = current->redirections;
	while (redir)
	{
		next_redir = redir->next;
		free(redir->filename);
		free(redir);
		redir = next_redir;
	}
}