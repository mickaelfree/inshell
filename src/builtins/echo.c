/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/31 00:57:18 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"

static int	has_newline_option(char ***args)
{
	int	is_newline;

	is_newline = 1;
	while (**args && !strncmp(**args, "-n", 2))
	{
		is_newline = 0;
		(*args)++;
	}
	return (is_newline);
}

static void	print_arguments(char **args)
{
	while (*args)
	{
		write(1, *args, strlen(*args));
		if (*(args + 1))
			write(1, " ", 1);
		args++;
	}
}

int	builtin_echo(char **args, char ***envp)
{
	int	is_newline;

	(void)envp;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	args++;
	is_newline = has_newline_option(&args);
	print_arguments(args);
	if (is_newline)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
