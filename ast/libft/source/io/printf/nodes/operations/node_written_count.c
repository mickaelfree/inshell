/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_written_count.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:16 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:16 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

void	init_written_count_node(va_list av, t_printf_node *node)
{
	printf_node_extract_flags(av, node);
	node->type = NODE_TYPE_WRITTEN_COUNT;
	node->data.p = va_arg(av, void *);
	node->string_len = 0;
}

int	dump_written_count_node(t_printf_output *out, t_printf_node *node)
{
	int	*written_count;

	written_count = (int *)node->data.p;
	*written_count = (int) out->cursor;
	return (0);
}
