/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:19 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:19 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"

int	ft_printf_write_hex(t_printf_output *out, uint64_t n, \
		int padding, bool upper)
{
	int	count;

	count = 0;
	if (padding > 0)
		count = ft_printf_write_hex(out, n / 16, padding - 1, upper);
	if (count < 0)
		return (count);
	if (upper)
		count += ft_printf_write(out, &"0123456789ABCDEF"[n % 16], 1);
	else
		count += ft_printf_write(out, &"0123456789abcdef"[n % 16], 1);
	return (count);
}

int	ft_printf_write_ll(t_printf_output *out, int64_t n, \
		int padding, bool write_sign)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		if (write_sign)
			count = ft_printf_write(out, "-", 1);
		padding--;
		n = -n;
	}
	if (count < 0)
		return (count);
	if (padding > 0)
		count = ft_printf_write_ll(out, n / 10, padding - 1, write_sign);
	if (count < 0)
		return (count);
	return (ft_printf_write(out, &"0123456789"[n % 10], 1));
}

int	ft_printf_write_llu(t_printf_output *out, uint64_t n, int padding)
{
	int	count;

	count = 0;
	if (padding > 0)
		count = ft_printf_write_llu(out, n / 10, padding - 1);
	if (count < 0)
		return (count);
	count += ft_printf_write(out, &"0123456789"[n % 10], 1);
	return (count);
}

int	ft_printf_pad(t_printf_output *out, char c, int padding)
{
	while (padding-- > 0)
	{
		if (ft_printf_write(out, &c, 1) == FAILURE)
			return (FAILURE);
	}
	return (0);
}
