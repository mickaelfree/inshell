/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:01:57 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:01:57 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "ft_printf/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list			argv;
	int				write_count;

	va_start(argv, format);
	write_count = ft_vdprintf(STDOUT_FILENO, format, argv);
	va_end(argv);
	return (write_count);
}

int	ft_vprintf(const char *format, va_list argv)
{
	return (ft_vdprintf(STDOUT_FILENO, format, argv));
}
