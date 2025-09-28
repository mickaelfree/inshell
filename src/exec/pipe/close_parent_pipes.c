/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_parent_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:12:13 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 06:34:17 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_error.h>
#include <ft_structs.h>
#include <unistd.h>

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
