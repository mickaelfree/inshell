/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 07:31:36 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/06 20:33:22 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar_fsize_incr(char c, int fd, size_t *fsize)
{
	if (fd < 0)
		return (0);
	(*fsize) += write(fd, &c, 1);
	return (1);
}

static void	ft_putstr_fsize_incr(char *s, int fd, size_t *fsize)
{
	if (!s)
	{
		(*fsize) += write(fd, "(null)", 6);
		return ;
	}
	(*fsize) += ft_strlen(s);
	if (write(fd, s, ft_strlen(s)) < 0)
		return ;
}

static void	ft_pointer_action(unsigned long args, int fd, size_t *fsize)
{
	if (args == 0)
	{
		(*fsize) += write(fd, "(nil)", 5);
		return ;
	}
	(*fsize) += write(fd, "0x", 2);
	ft_putnbr_base_ul(args, "0123456789abcdef", fd, fsize);
}

int	ft_printf_parse(char current, va_list args, size_t *fsize)
{
	if (current == 'c')
		ft_putchar_fsize_incr(va_arg(args, int), 1, fsize);
	else if (current == 's')
		ft_putstr_fsize_incr(va_arg(args, char *), 1, fsize);
	else if (current == 'p')
		ft_pointer_action(va_arg(args, unsigned long), 1, fsize);
	else if (current == 'd' || current == 'i')
		ft_putnbr_int(va_arg(args, int), 1, fsize);
	else if (current == 'u')
		ft_putnbr_base_ul(va_arg(args, unsigned int), "0123456789", 1, fsize);
	else if (current == 'x')
		ft_putnbr_base_ul(va_arg(args, unsigned int), "0123456789abcdef", 1,
			fsize);
	else if (current == 'X')
		ft_putnbr_base_ul(va_arg(args, unsigned int), "0123456789ABCDEF", 1,
			fsize);
	else if (current == '%')
	{
		ft_putchar_fd('%', 1);
		(*fsize)++;
	}
	return (0);
}
