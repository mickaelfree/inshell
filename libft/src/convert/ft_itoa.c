/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:06:04 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 19:19:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_calc_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	num;

	len = ft_calc_len(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	num = n;
	if (n < 0)
		num = -n;
	res[len] = '\0';
	while (len-- != 0)
	{
		res[len] = num % 10 + 48;
		num /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
