/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:21:42 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/06 20:31:59 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
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
			write(STDERR_FILENO, " numeric argument required\n", 26);
			exit(256);
		}
		i++;
	}
	return (result * sign);
}
int	builtin_exit(char **args, char ***envp)
{
        long status =-117;
	if (args[1] && !is_numeric(args[1]))
	{
		write(STDERR_FILENO, " numeric argument required\n", 26);
	        if (envp && *envp)
	        	ft_free_env(*envp);
		exit(2);
	}
	if (args[1] && args[2])
	{
		write(STDERR_FILENO, " too many arguments\n", 19);
                g_last_exit_status = 2;
		return (2);
	}
	if (!args[1])
        {
                if (envp && *envp)
                        ft_free_env(*envp);
		exit(0);
        }
        status = ft_atol(args[1]);
        if (envp && *envp)
               ft_free_env(*envp);
	exit((unsigned char)status);
}
