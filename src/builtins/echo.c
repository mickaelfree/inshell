/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/18 16:21:55 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// TODO::
#include "../../includes/inshell.h"

static int	has_newline_option(char ***args)
{
	int	newline;

	newline = 1;
	while (**args && !strncmp(**args, "-n", 2))
	{
		newline = 0;
		(*args)++;
	}
	return (newline);
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
	int	newline;

	(void)envp;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	args++;
	newline = has_newline_option(&args);
	print_arguments(args);
	if (newline)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
