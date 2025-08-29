/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:01:56 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:01:56 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "ft_printf/ft_printf.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list			argv;
	int				write_count;

	va_start(argv, format);
	write_count = ft_vdprintf(fd, format, argv);
	va_end(argv);
	return (write_count);
}

int	ft_vdprintf(int fd, const char *format, va_list argv)
{
	t_printf_data	data;

	data.format = format;
	data.output.mode = PRINTF_OUTPUT_FD;
	data.output.fd = fd;
	return (_ft_printf_internal(&data, argv));
}
