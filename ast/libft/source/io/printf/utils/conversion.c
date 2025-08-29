/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:17 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:17 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/utils.h"

unsigned int	ft_strtoui(char *nptr, char **endptr)
{
	unsigned int	nb;

	nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + *nptr - '0';
		nptr++;
	}
	*endptr = nptr;
	return (nb);
}

int	int_strlen(int64_t n, int base, bool count_sign)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		if (count_sign)
			count++;
	}
	while (n >= (int64_t)base)
	{
		n /= base;
		count++;
	}
	return (count);
}

int	uint_strlen(uint64_t n, int base)
{
	int	count;

	count = 1;
	while (n >= (uint64_t)base)
	{
		n /= base;
		count++;
	}
	return (count);
}
