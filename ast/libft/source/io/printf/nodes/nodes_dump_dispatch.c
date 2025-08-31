/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_dump_dispatch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:02 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:02 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"

int	dump_nodes(t_printf_data *data)
{
	t_printf_node	*node;
	int				total_len;
	int				res;

	total_len = get_nodes_total_len(data->nodes);
	node = data->nodes;
	while (node)
	{
		res = dump_node(&data->output, node);
		if (res < 0)
		{
			if (res == FAILURE)
				break ;
			return (res);
		}
		node = node->next;
	}
	return (total_len);
}

int	dump_node(t_printf_output *out, t_printf_node *node)
{
	if (node->type == NODE_TYPE_CHAR)
		return (dump_char_node(out, node));
	if (node->type == NODE_TYPE_STRING)
		return (dump_string_node(out, node));
	if (node->type == NODE_TYPE_POINTER)
		return (dump_pointer_node(out, node));
	if (node->type == NODE_TYPE_INTEGER || node->type == NODE_TYPE_UNSIGNED)
		return (dump_int_node(out, node));
	if (node->type == NODE_TYPE_HEX_LOWER || node->type == NODE_TYPE_HEX_UPPER)
		return (dump_hex_node(out, node));
	if (node->type == NODE_TYPE_WRITTEN_COUNT)
		return (dump_written_count_node(out, node));
	if (node->type == NODE_TYPE_PERCENT)
		return (dump_percent_node(out));
	if (node->type == NODE_TYPE_TEXT)
		return (dump_text_node(out, node));
	return (FAILURE);
}
