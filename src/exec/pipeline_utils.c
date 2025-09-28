/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:12:13 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 02:03:16 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "error.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	count_pipeline(t_command *cmds)
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

t_pipeline	*create_pipeline(int cmd_count)
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
		pipeline->pipes = malloc(pipeline->pipe_count * sizeof(int [2]));
	if (!pipeline->pids || (cmd_count > 1 && !pipeline->pipes))
	{
		print_custom_error(ERR_ALLOC_PIPE_UTILS);
		free(pipeline->pids);
		free(pipeline->pipes);
		free(pipeline);
		return (NULL);
	}
	return (pipeline);
}

void	destroy_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free(pipeline->pids);
	free(pipeline->pipes);
	free(pipeline);
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

void	close_parent_pipes(t_pipeline *pipeline)
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
