/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:01:59 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:01:59 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	argv;
	int		write_count;

	va_start(argv, format);
	write_count = ft_vsnprintf(str, SIZE_MAX, format, argv);
	va_end(argv);
	return (write_count);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	argv;
	int		write_count;

	va_start(argv, format);
	write_count = ft_vsnprintf(str, size, format, argv);
	va_end(argv);
	return (write_count);
}

int	ft_vsprintf(char *str, const char *format, va_list argv)
{
	return (ft_vsnprintf(str, SIZE_MAX, format, argv));
}

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list argv)
{
	t_printf_data	data;

	data.format = format;
	data.output.mode = PRINTF_OUTPUT_BUFFER;
	data.output.buffer = str;
	data.output.size = size;
	data.output.cursor = 0;
	return (_ft_printf_internal(&data, argv));
}
