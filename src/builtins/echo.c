/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/26 18:20:20 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"

static int	has_newline_option(char ***args)
{
	int		nline;
	char	*arg;
	int		i;

	nline = 1;
	while (**args && ***args == '-')
	{
		arg = **args;
		i = 1;
		if (!arg[i])
			break ;
		while (arg[i] && arg[i] == 'n')
			i++;
		if (arg[i] != '\0')
			break ;
		nline = 0;
		(*args)++;
	}
	return (nline);
}

static void	print_arguments(char **args)
{
	int i;

	i = 0;
	while (*args)
	{
		if (*args[i] == '$')
			i++;
		write(1, *args + i, ft_strlen(*args));
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
