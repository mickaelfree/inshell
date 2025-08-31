/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:10 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/11 06:14:55 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

void	init_int_node(va_list av, t_printf_node *node, bool is_unsigned)
{
	printf_node_extract_flags(av, node);
	if (!is_unsigned)
	{
		node->type = NODE_TYPE_INTEGER;
		node->data.u = va_arg(av, int);
	}
	else
	{
		node->type = NODE_TYPE_UNSIGNED;
		node->data.d = va_arg(av, unsigned int);
	}
}

int	get_int_node_len(t_printf_node *node)
{
	int		len;

	get_int_node_lens(node, NULL, &len);
	if (get_int_node_sign(node) != 0)
		++len;
	node->string_len = int_max(node->width, len);
	return (node->string_len);
}

int	dump_int_node(t_printf_output *out, t_printf_node *node)
{
	uint64_t	abs_val;
	int			raw_len;
	int			len;
	int			pad_len;
	char		sign;

	get_int_node_lens(node, &raw_len, &len);
	abs_val = get_int_node_raw_value(node);
	sign = get_int_node_sign(node);
	pad_len = 0;
	if (node->width > len + (sign != 0))
		pad_len = node->width - len - (sign != 0);
	if (!node->flag_minus)
	{
		if (dump_int_lpad(out, node, pad_len, sign) == FAILURE)
			return (FAILURE);
	}
	else if (sign != 0 && ft_printf_write(out, &sign, 1) == FAILURE)
		return (FAILURE);
	if (raw_len > 0 && ft_printf_write_llu(out, abs_val, len - 1) == FAILURE)
		return (FAILURE);
	if (node->flag_minus && ft_printf_pad(out, ' ', pad_len) == FAILURE)
		return (FAILURE);
	return (0);
}
