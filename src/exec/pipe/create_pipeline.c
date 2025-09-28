/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 06:22:08 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 07:00:20 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_error.h>
#include <ft_structs.h>
#include <stdlib.h>
#include <unistd.h>

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
