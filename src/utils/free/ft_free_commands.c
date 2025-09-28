/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:43:41 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 00:46:08 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include<ft_structs.h>
#include<utils.h>
#include<stdlib.h>

void	ft_free_commands(t_command *head)
{
	t_command	*current;
	t_command	*next;

	current = head;
	while (current)
	{
		next = current->next;
		ft_free_args_and_redir(current);
		free(current->input_file);
		free(current->output_file);
		free(current->heredoc_delim);
		free(current);
		current = next;
	}
}