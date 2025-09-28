/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 06:21:20 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 06:34:48 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_structs.h>

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
