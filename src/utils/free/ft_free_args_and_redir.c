/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_args_and_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:39:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 00:42:21 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include<ft_structs.h>
#include<stdlib.h>

void	ft_free_args_and_redir(t_command *current)
{
	t_redirection	*redir;
	t_redirection	*next_redir;
	int				i;

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
