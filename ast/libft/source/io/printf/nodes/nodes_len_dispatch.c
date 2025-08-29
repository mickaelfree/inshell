/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_len_dispatch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:04 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:04 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/nodes.h"

int	get_nodes_total_len(t_printf_node *nodes)
{
	int	total_len;

	total_len = 0;
	while (nodes)
	{
		total_len += get_node_len(nodes);
		nodes = nodes->next;
	}
	return (total_len);
}

int	get_node_len(t_printf_node *node)
{
	if (node->type == NODE_TYPE_CHAR)
		return (get_char_node_len(node));
	if (node->type == NODE_TYPE_STRING)
		return (get_string_node_len(node));
	if (node->type == NODE_TYPE_POINTER)
		return (get_pointer_node_len(node));
	if (node->type == NODE_TYPE_INTEGER || node->type == NODE_TYPE_UNSIGNED)
		return (get_int_node_len(node));
	if (node->type == NODE_TYPE_HEX_LOWER || node->type == NODE_TYPE_HEX_UPPER)
		return (get_hex_node_len(node));
	if (node->type == NODE_TYPE_WRITTEN_COUNT)
		return (0);
	if (node->type == NODE_TYPE_PERCENT)
		return (get_percent_node_len(node));
	if (node->type == NODE_TYPE_TEXT)
		return (get_text_node_len(node));
	return (0);
}
