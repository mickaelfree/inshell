/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_hex_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:09 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:09 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

void	get_hex_node_lens(t_printf_node *node, int *raw_len, int *len)
{
	int	local_raw_len;
	int	local_len;

	local_raw_len = 0;
	if (node->precision != 0 || node->data.u != 0)
		local_raw_len = uint_strlen((uint64_t)node->data.u, 16);
	if (node->precision >= 0)
		local_len = int_max(node->precision, local_raw_len);
	else
		local_len = local_raw_len;
	if (node->flag_hash && node->data.u != 0)
		local_len += 2;
	if (raw_len)
		*raw_len = local_raw_len;
	if (len)
		*len = local_len;
}

int	dump_hex_prefix(t_printf_output *out, t_printf_node *node)
{
	if (!node->flag_hash || node->data.u == 0)
		return (0);
	if (node->type == NODE_TYPE_HEX_LOWER)
	{
		if (ft_printf_write(out, "0x", 2) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (ft_printf_write(out, "0X", 2) == FAILURE)
			return (FAILURE);
	}
	return (0);
}

int	dump_hex_lpad(t_printf_output *out, t_printf_node *node, int p_len)
{
	if (node->flag_minus)
		return (dump_hex_prefix(out, node));
	if (node->flag_zero && node->precision == VALUE_UNSET)
	{
		if (dump_hex_prefix(out, node) == FAILURE)
			return (FAILURE);
		if (ft_printf_pad(out, '0', p_len) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (ft_printf_pad(out, ' ', p_len) == FAILURE)
			return (FAILURE);
		if (dump_hex_prefix(out, node) == FAILURE)
			return (FAILURE);
	}
	return (0);
}
