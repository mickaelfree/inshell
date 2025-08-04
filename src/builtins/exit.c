/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:21:42 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/04 18:06:45 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
static long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	result;
	long	prev;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = result;
		result = result * 10 + (str[i] - '0');
		if ((result - (str[i] - '0')) / 10 != prev)
		{
			printf("exit: %s: numeric argument required\n", str);
			exit(2);
		}
		i++;
	}
	return (result * sign);
}
int	builtin_exit(char **args, char ***envp)
{
        (void)envp;
	if (args[1] && !is_numeric(args[1]))
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[1] && args[2])
	{
		printf("exit: too many arguments\n");
	}
	if (!args[1])
		exit(0);
	else
		exit(ft_atol(args[1]));
}
