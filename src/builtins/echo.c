/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/02 01:33:34 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

static int	has_newline_option(char ***args)
{
	int	nline;

	nline = 1;
	while (**args && !strncmp(**args, "-n", 2))
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
		write(1, *args, strlen(*args));
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

int	builtin_echo_ast(t_ast *node, char ***envp)
{

	(void)envp;
	if (!node)
	{
		printf("node null\n");
		return (EXIT_SUCCESS);
	}
	if (node->type != AST_WORD || !node->token)
	{
		printf("wrong node type\n");
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd(node->token, 1);
		if (node->left)
		{
			write(1, " ", 1);
			builtin_echo_ast(node->left, envp);
		}
		else
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
