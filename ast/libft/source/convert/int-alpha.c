/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int-alpha.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:01:52 by jureix-c          #+#    #+#             */
/*   Updated: 2025/05/05 18:48:14 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

static inline int		ft_calculate_itoa_len(int n);
static inline int		ft_abs(int n);

int	ft_atoi(const char *nptr)
{
	uint64_t	res;
	int			sign;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr++ - '0';
		if (sign == 1 && res > (uint64_t) LONG_MAX)
			return (-1);
		if (sign == -1 && res > - (uint64_t) LONG_MIN)
			return (0);
	}
	return (res * sign);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		cur;

	cur = ft_calculate_itoa_len(n);
	dst = malloc(sizeof(char) * cur);
	if (!dst)
		return (NULL);
	dst[--cur] = '\0';
	if (n < 0)
		dst[0] = '-';
	if (n == 0)
		dst[0] = '0';
	while (n)
	{
		dst[--cur] = ft_abs(n % 10) + 48;
		n /= 10;
	}
	return (dst);
}

static inline int	ft_calculate_itoa_len(int n)
{
	int	len;

	len = 1 + (n < 0);
	if (n == 0)
		len++;
	while (n && len++)
		n /= 10;
	return (len);
}

static inline int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}
