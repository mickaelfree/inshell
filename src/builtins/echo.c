/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/02 19:46:44 by zsonie           ###   ########lyon.fr   */
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

///* ************************************************************************** */
/*                                    NEW                                       */
///* ************************************************************************** */

static int check_node(t_ast *node)
{
	if (!node)
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int check_n_flag(char *token)
{
    if (!token || ft_strncmp(token, "-n", 2) != 0)
        return (0);
    
    char *ptr = token + 2;
    while (*ptr == 'n')
        ptr++;

    return (*ptr == '\0');
}

int builtin_echo_ast(t_ast *node)
{
    int suppress_newline = 0;
    t_ast *current = node;
    int first_output = 1;
    
	if (check_node(current) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
    while (current && current->type == AST_WORD && current->token && 
           check_n_flag(current->token))
    {
        suppress_newline = 1;
        current = current->left;
    }
    while (current && current->type == AST_WORD && current->token)
    {
        if (!first_output)
            write(1, " ", 1);
        ft_putstr_fd(current->token, 1);
        first_output = 0;
        current = current->left;
    }
    if (!suppress_newline)
        write(1, "\n", 1);
    return (EXIT_SUCCESS);
}
