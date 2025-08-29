/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:14 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/25 13:31:54 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

void	init_string_node(va_list av, t_printf_node *node)
{
	node->type = NODE_TYPE_STRING;
	printf_node_extract_flags(av, node);
	node->data.s = (char *) va_arg(av, char *);
}

int	get_string_node_len(t_printf_node *node)
{
	if (node->data.s == NULL)
		node->string_len = 6 * (node->precision < 0 || node->precision > 5);
	else
		node->string_len = ft_strlen(node->data.s);
	if (node->precision >= 0)
		node->string_len = int_min(node->string_len, node->precision);
	node->string_len = int_max(node->string_len, node->width);
	return (node->string_len);
}

int	dump_string_pad(t_printf_output *out, t_printf_node *node, int raw_len)
{
	int	p_len;

	if (node->width <= raw_len && raw_len <= node->precision)
		return (0);
	p_len = node->width;
	if (node->data.s == NULL)
		p_len -= 6 * (node->precision < 0 || node->precision > 5);
	else if (node->precision >= 0)
		p_len -= int_min(raw_len, node->precision);
	else
		p_len -= raw_len;
	if (ft_printf_pad(out, ' ', p_len) == FAILURE)
		return (FAILURE);
	return (0);
}

int	dump_string_node(t_printf_output *out, t_printf_node *node)
{
	int	raw_len;

	raw_len = 0;
	if (node->data.s != NULL)
	{
		if (node->precision == VALUE_UNSET)
			raw_len = ft_strlen(node->data.s);
		else
			raw_len = ft_strnlen(node->data.s, node->precision);
	}
	if (node->flag_minus == 0 && dump_string_pad(out, node, raw_len) == FAILURE)
		return (FAILURE);
	if (node->data.s == NULL)
	{
		if (node->precision == VALUE_UNSET || node->precision > 5)
			ft_printf_write(out, "(null)", 6);
	}
	else if (ft_printf_write(out, node->data.s, raw_len) == FAILURE)
		return (FAILURE);
	if (node->flag_minus && dump_string_pad(out, node, raw_len) == FAILURE)
		return (FAILURE);
	return (0);
}
