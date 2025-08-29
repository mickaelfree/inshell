/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_int_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:11 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/11 06:14:59 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

uint64_t	get_int_node_raw_value(t_printf_node *node)
{
	uint64_t	value;

	if (node->type == NODE_TYPE_INTEGER)
	{
		if (node->data.d < 0)
			value = -(uint64_t) node->data.d;
		else
			value = node->data.d;
	}
	else
		value = node->data.u;
	return (value);
}

char	get_int_node_sign(t_printf_node *node)
{
	if (node->type == NODE_TYPE_INTEGER)
	{
		if (node->data.d < 0)
			return ('-');
		else if (node->flag_plus)
			return ('+');
		else if (node->flag_space)
			return (' ');
	}
	return (0);
}

void	get_int_node_lens(t_printf_node *node, int *raw_len, int *len)
{
	int	local_raw_len;
	int	local_len;

	local_raw_len = 0;
	if (node->type == NODE_TYPE_INTEGER)
	{
		if (node->precision != 0 || node->data.d != 0)
			local_raw_len = int_strlen((int64_t) node->data.d, 10, false);
	}
	else if (node->precision != 0 || node->data.u != 0)
		local_raw_len = uint_strlen((uint64_t)node->data.u, 10);
	if (node->precision >= 0)
		local_len = int_max(node->precision, local_raw_len);
	else
		local_len = local_raw_len;
	if (raw_len)
		*raw_len = local_raw_len;
	if (len)
		*len = local_len;
}

int	dump_int_lpad(t_printf_output *out, t_printf_node *node, int p_len, char s)
{
	if (node->flag_zero && node->precision == VALUE_UNSET)
	{
		if (s != 0 && ft_printf_write(out, &s, 1) == FAILURE)
			return (FAILURE);
		if (ft_printf_pad(out, '0', p_len) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (ft_printf_pad(out, ' ', p_len) == FAILURE)
			return (FAILURE);
		if (s != 0 && ft_printf_write(out, &s, 1) == FAILURE)
			return (FAILURE);
	}
	return (0);
}
