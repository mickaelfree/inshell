/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:08 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:08 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

void	init_hex_node(va_list av, t_printf_node *node, bool is_upper)
{
	printf_node_extract_flags(av, node);
	if (!is_upper)
		node->type = NODE_TYPE_HEX_LOWER;
	else
		node->type = NODE_TYPE_HEX_UPPER;
	node->data.u = va_arg(av, unsigned int);
}

int	get_hex_node_len(t_printf_node *node)
{
	int		len;

	get_hex_node_lens(node, NULL, &len);
	node->string_len = int_max(node->width, len);
	return (node->string_len);
}

int	dump_hex_node(t_printf_output *out, t_printf_node *node)
{
	int			raw_len;
	int			len;
	int			pad_len;
	int			out_len;
	bool		upper;

	get_hex_node_lens(node, &raw_len, &len);
	upper = node->type == NODE_TYPE_HEX_UPPER;
	pad_len = 0;
	if (node->width > len)
		pad_len = node->width - len;
	if (dump_hex_lpad(out, node, pad_len) == FAILURE)
		return (FAILURE);
	if (raw_len > 0)
	{
		out_len = len - 1 - node->flag_hash * 2;
		if (ft_printf_write_hex(out, node->data.u, out_len, upper) == FAILURE)
			return (FAILURE);
	}
	if (node->flag_minus && ft_printf_pad(out, ' ', pad_len) == FAILURE)
		return (FAILURE);
	return (0);
}
