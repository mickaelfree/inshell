/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 06:23:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 06:31:05 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <mandatoshell.h>
#include <stdio.h>
#include <unistd.h>

int	setup_child_pipes(int index, t_pipeline *pipeline)
{
	if (index > 0)
	{
		if (dup2(pipeline->pipes[index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (0);
		}
	}
	if (index < pipeline->cmd_count - 1)
	{
		if (dup2(pipeline->pipes[index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (0);
		}
	}
	return (1);
}

int	setup_pipes(t_pipeline *pipeline)
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
