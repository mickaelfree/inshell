/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:12 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:12 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"

void	init_percent_node(va_list av, t_printf_node *node)
{
	node->type = NODE_TYPE_PERCENT;
	printf_node_extract_flags(av, node);
}

int	get_percent_node_len(t_printf_node *node)
{
	node->string_len = 1;
	return (node->string_len);
}

int	dump_percent_node(t_printf_output *out)
{
	return (ft_printf_write(out, "%", 1));
}
