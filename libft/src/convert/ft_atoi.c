/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarunomane <sarunomane@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:29 by zsonie            #+#    #+#             */
/*   Updated: 2025/02/14 21:20:14 by sarunomane       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>

static void	ft_space_and_sign_increment(const char *str, size_t *i, int *sign)
{
	*i = 0;
	while (str[*i] && ((str[*i] == ' ') || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
	*sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	num;
	int		sign;

	num = 0;
	ft_space_and_sign_increment(str, &i, &sign);
	while (str[i] && !(str[i] < '0' || str[i] > '9'))
	{
		if (LONG_MAX / 10 < num)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		num *= 10;
		if (LONG_MAX - (str[i] - 48) < num)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		num += str[i] - '0';
		i++;
	}
	return (num * sign);
}
