/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_pointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:13 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:13 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

void	init_pointer_node(va_list av, t_printf_node *node)
{
	node->type = NODE_TYPE_POINTER;
	printf_node_extract_flags(av, node);
	node->data.p = va_arg(av, void *);
}

int	get_pointer_node_raw_len(t_printf_node *node)
{
	int	raw_len;

	if (node->data.p == NULL)
		raw_len = 5;
	else
	{
		raw_len = uint_strlen((uint64_t) node->data.p, 16) + 2;
		if (node->flag_zero && !node->flag_minus)
			raw_len = int_max(raw_len, node->width);
	}
	return (raw_len);
}

int	get_pointer_node_len(t_printf_node *node)
{
	node->string_len = int_max(get_pointer_node_raw_len(node), node->width);
	return (node->string_len);
}

int	dump_pointer_pad(t_printf_output *out, t_printf_node *node, int raw_len)
{
	int	p_len;

	if (raw_len >= node->width)
		return (0);
	p_len = node->width - raw_len;
	if (ft_printf_pad(out, ' ', p_len) == FAILURE)
		return (FAILURE);
	return (0);
}

int	dump_pointer_node(t_printf_output *out, t_printf_node *node)
{
	uint64_t	p;
	int			raw_len;
	int			out_len;

	p = (uint64_t) node->data.p;
	raw_len = get_pointer_node_raw_len(node);
	if (!node->flag_minus && dump_pointer_pad(out, node, raw_len) == FAILURE)
		return (FAILURE);
	if (node->data.p == NULL)
	{
		if (ft_printf_write(out, "(nil)", raw_len) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (ft_printf_write(out, "0x", 2) == FAILURE)
			return (FAILURE);
		out_len = raw_len - 3;
		if (ft_printf_write_hex(out, p, out_len, false) == FAILURE)
			return (FAILURE);
	}
	if (node->flag_minus && dump_pointer_pad(out, node, raw_len) == FAILURE)
		return (FAILURE);
	return (0);
}
