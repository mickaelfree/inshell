/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:01 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:22:07 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

int	lex_node_params(const char *f, va_list av, t_printf_node *node)
{
	int	offset;
	int	ret_value;

	offset = 1;
	ret_value = lex_node_flags(f + offset, node);
	if (ret_value < 0)
		return (ret_value);
	offset += ret_value;
	ret_value = lex_node_widths(f + offset, node);
	if (ret_value < 0)
		return (ret_value);
	offset += ret_value;
	ret_value = lex_node_type(f + offset, av, node);
	if (ret_value < 0)
		return (ret_value);
	offset += ret_value;
	return (offset);
}

int	lex_node_flags(const char *f, t_printf_node *node)
{
	char	*match;
	int		i;

	i = 0;
	while (f[i])
	{
		match = ft_strchr(FT_PRINTF_FLAGS, f[i]);
		if (!match)
			break ;
		lex_node_flag(*match, node);
		++i;
	}
	return (i);
}

void	lex_node_flag(const char match, t_printf_node *node)
{
	if (match == '-')
		node->flag_minus++;
	else if (match == '0')
		node->flag_zero++;
	else if (match == '+')
		node->flag_plus++;
	else if (match == ' ')
		node->flag_space++;
	else if (match == '#')
		node->flag_hash++;
	else if (match == 'h')
		node->flag_h++;
	else if (match == 'l')
		node->flag_l++;
	else if (match == 'L')
		node->flag_bigl++;
	else if (match == 'j')
		node->flag_j++;
	else if (match == 'z')
		node->flag_z++;
	else if (match == 't')
		node->flag_t++;
}

int	lex_node_widths(const char *f, t_printf_node *node)
{
	char	*cursor;
	char	*temp;

	cursor = (char *) f;
	node->width = (int) ft_strtoui(cursor, &cursor);
	if (cursor == f && *cursor == '*')
	{
		node->width = VALUE_FROM_ARG;
		++cursor;
	}
	if (*cursor == '.')
	{
		temp = ++cursor;
		node->precision = (int) ft_strtoui(cursor, &cursor);
		if (cursor == temp && *cursor == '*')
		{
			node->precision = VALUE_FROM_ARG;
			++cursor;
		}
	}
	return (cursor - f);
}

int	lex_node_type(const char *f, va_list av, t_printf_node *node)
{
	char	*match;

	match = ft_strchr(FT_PRINTF_MODIFIERS, *f);
	if (!match)
		return (FAILURE);
	else if (*match == 'c')
		init_char_node(av, node);
	else if (*match == 's')
		init_string_node(av, node);
	else if (*match == 'p')
		init_pointer_node(av, node);
	else if (*match == 'd' || *match == 'i' || *match == 'u')
		init_int_node(av, node, *match == 'u');
	else if (*match == 'x' || *match == 'X')
		init_hex_node(av, node, *match == 'X');
	else if (*match == 'n')
		init_written_count_node(av, node);
	else if (*match == '%')
		init_percent_node(av, node);
	return (1);
}
