/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/03 01:54:50 by zsonie           ###   ########lyon.fr   */
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

static void skip_n(int *i, char *args_str, int len, int *found_n_flag)
{
    while (*i < len)
    {
        while (*i < len && args_str[*i] == ' ')
            (*i)++;
        if (*i >= len)
            break;
        if (args_str[*i] == '-' && *i + 1 < len && args_str[*i + 1] == 'n')
        {
            int start = *i;
            *i += 2;
            while (*i < len && args_str[*i] == 'n')
                (*i)++;
            if (*i < len && args_str[*i] != ' ')
            {
                *i = start;
                break;
            }
            *found_n_flag = 1;
        }
        else
            break;
    }
}


static char *skip_n_flags(char *args_str, int *suppress_newline)
{
    int	i;
    int found_n_flag;
    int len;

	i = 0;
	found_n_flag = 0;
	len = ft_strlen(args_str);
	skip_n(&i, args_str, len, &found_n_flag);
    while (i < len && args_str[i] == ' ')
        i++;
    *suppress_newline = found_n_flag;
    if (i < len)
		return (ft_strdup(&args_str[i]));
	else
		return (ft_strdup(""));
}


int builtin_echo_ast(t_ast *node)
{
    int suppress_newline = 0;
    char *args_to_print;
    
    if (!node || !node->token)
    {
        write(1, "\n", 1);
        return EXIT_SUCCESS;
    }
    
    args_to_print = skip_n_flags(node->token, &suppress_newline);
    
    if (args_to_print && *args_to_print)
        ft_putstr_fd(args_to_print, 1);
    if (!suppress_newline)
        write(1, "\n", 1);
    if (args_to_print)
        free(args_to_print);
    
    return EXIT_SUCCESS;
}
