/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:06 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:06 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"

void	init_char_node(va_list av, t_printf_node *node)
{
	node->type = NODE_TYPE_CHAR;
	printf_node_extract_flags(av, node);
	node->data.c = (char) va_arg(av, int);
}

int	get_char_node_len(t_printf_node *node)
{
	node->string_len = 1;
	if (node->width > 1)
		node->string_len = node->width;
	return (node->string_len);
}

int	dump_char_node(t_printf_output *out, t_printf_node *node)
{
	if (node->flag_minus)
	{
		if (ft_printf_write(out, &(node->data.c), 1) <= 0)
			return (-1);
	}
	while (node->width-- > 1)
	{
		if (ft_printf_write(out, " ", 1) <= 0)
			return (-1);
	}
	if (!node->flag_minus)
	{
		if (ft_printf_write(out, &(node->data.c), 1) <= 0)
			return (-1);
	}
	return (0);
}
