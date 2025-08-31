/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:05 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:05 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_printf/nodes.h"

t_printf_node	*printf_node_new(void)
{
	t_printf_node	*node;

	node = malloc(sizeof(t_printf_node));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->type = NODE_TYPE_TEXT;
	node->data.p = NULL;
	node->string_len = 0;
	node->flag_minus = 0;
	node->flag_zero = 0;
	node->flag_plus = 0;
	node->flag_space = 0;
	node->flag_hash = 0;
	node->width = VALUE_UNSET;
	node->precision = VALUE_UNSET;
	return (node);
}

void	printf_node_add_back(t_printf_node *nodes, t_printf_node *node)
{
	if (!node)
		return ;
	nodes = printf_node_last(nodes);
	if (!nodes)
		return ;
	nodes->next = node;
}

void	printf_nodes_clean(t_printf_node *nodes)
{
	t_printf_node	*node;

	while (nodes)
	{
		node = nodes;
		nodes = nodes->next;
		free(node);
	}
}
