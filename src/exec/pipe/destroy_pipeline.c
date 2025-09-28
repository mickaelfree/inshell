/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 06:23:04 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 06:34:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_structs.h>
#include <stdlib.h>

void	destroy_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free(pipeline->pids);
	free(pipeline->pipes);
	free(pipeline);
}
