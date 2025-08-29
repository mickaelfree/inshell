/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:00 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:00 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

int	lex_nodes(t_printf_data *data, va_list av)
{
	t_printf_node	*current;
	int				node_offset;
	int				i;

	i = 0;
	while (data->format[i])
	{
		current = printf_node_new();
		if (!current)
			return (MALLOC_ERROR);
		if (!data->nodes)
			data->nodes = current;
		else
			printf_node_add_back(data->nodes, current);
		node_offset = lex_node(data->format + i, av, current);
		if (node_offset < 0)
			return (node_offset);
		i += node_offset;
	}
	return (0);
}

int	lex_node(const char *f, va_list av, t_printf_node *node)
{
	int	offset;

	offset = 0;
	if (f[0] != '%')
	{
		node->data.s = f;
		while (f[offset] && f[offset] != '%')
			offset++;
		node->string_len = offset;
	}
	else
		offset = lex_node_params(f, av, node);
	return (offset);
}
