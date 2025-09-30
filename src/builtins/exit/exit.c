/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:21:42 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 19:54:36 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"
#include "ft_convert.h"
#include "ft_structs.h"
#include "ft_utils.h"
#include "mandatoshell.h"
#include "stdlib.h"
#include "unistd.h"

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

static void	exit_with_cleanup(t_command *head, t_command *cmd, char ***envp,
		int code)
{
	if (head)
		ft_free_commands(head);
	else if (cmd)
		ft_free_commands(cmd);
	if (envp && *envp)
		ft_free_env(*envp);
	exit(code);
}

int	builtin_exit(t_command *cmd, char **args, char ***envp)
{
	long	status;

	if (args[1] && !is_numeric(args[1]))
	{
		write(STDERR_FILENO, " numeric argument required\n", 27);
		exit_with_cleanup(NULL, cmd, envp, 2);
	}
	if (args[1] && args[2])
	{
		write(STDERR_FILENO, " too many arguments\n", 20);
		g_last_exit_status = 2;
		return (2);
	}
	if (!args[1])
		exit_with_cleanup(NULL, cmd, envp, 0);
	status = ft_atoi(args[1]);
	exit_with_cleanup(NULL, cmd, envp, (unsigned char)status);
	return (0);
}

int	builtin_exit_child(t_command *head, t_command *cmd, char **args,
		char ***envp)
{
	long	status;

	if (args[1] && !is_numeric(args[1]))
	{
		write(STDERR_FILENO, " numeric argument required\n", 27);
		exit_with_cleanup(head, cmd, envp, 2);
	}
	if (args[1] && args[2])
	{
		write(STDERR_FILENO, " too many arguments\n", 20);
		g_last_exit_status = 2;
		return (2);
	}
	if (!args[1])
		exit_with_cleanup(head, cmd, envp, 0);
	status = ft_atoi(args[1]);
	exit_with_cleanup(head, cmd, envp, (unsigned char)status);
	return (0);
}
