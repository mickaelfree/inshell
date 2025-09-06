/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/06 20:28:49 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "libft.h"

static int	has_newline_option(char ***args)
{
	int	nline;

	nline = 1;
	while (**args && !ft_strncmp(**args, "-n", 2))
	{
		nline = 0;
		(*args)++;
	}
	return (nline);
}

static void	print_arguments(char **args)
{
	while (*args)
	{
		write(1, *args, ft_strlen(*args));
		if (*(args + 1))
			write(1, " ", 1);
		args++;
	}
}

int	builtin_echo(char **args, char ***envp)
{
	int	nline;

	(void)envp;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	args++;
	nline = has_newline_option(&args);
	print_arguments(args);
	if (nline)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
