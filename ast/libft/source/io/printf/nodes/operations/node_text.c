/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:15 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:15 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"

int	get_text_node_len(t_printf_node *node)
{
	return (node->string_len);
}

int	dump_text_node(t_printf_output *out, t_printf_node *node)
{
	return (ft_printf_write(out, node->data.s, node->string_len));
}
