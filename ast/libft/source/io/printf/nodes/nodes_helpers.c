/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:03 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:03 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_printf/nodes.h"

t_printf_node	*printf_node_last(t_printf_node *nodes)
{
	if (!nodes)
		return (NULL);
	while (nodes->next)
		nodes = nodes->next;
	return (nodes);
}

void	printf_node_extract_flags(va_list av, t_printf_node *node)
{
	if (node->width == VALUE_FROM_ARG)
		node->width = va_arg(av, int);
	if (node->precision == VALUE_FROM_ARG)
		node->precision = va_arg(av, int);
}
