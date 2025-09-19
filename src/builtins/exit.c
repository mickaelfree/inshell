/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:21:42 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/19 22:33:51 by mickmart         ###   ########.fr       */
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

static void	exit_with_cleanup(char ***envp, int code)
{
	if (envp && *envp)
		ft_free_env(*envp);
	exit(code);
}

int	builtin_exit(char **args, char ***envp)
{
	long	status;

	if (args[1] && !is_numeric(args[1]))
	{
		write(STDERR_FILENO, " numeric argument required\n", 26);
		exit_with_cleanup(envp, 2);
	}
	if (args[1] && args[2])
	{
		write(STDERR_FILENO, " too many arguments\n", 19);
		g_last_exit_status = 2;
		return (2);
	}
	if (!args[1])
		exit_with_cleanup(envp, 0);
	status = ft_atoi(args[1]);
	exit_with_cleanup(envp, (unsigned char)status);
	return (0);
}
