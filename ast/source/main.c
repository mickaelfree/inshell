/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:33:13 by jureix-c          #+#    #+#             */
/*   Updated: 2025/06/09 13:52:45 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"

static int	quotes_handler(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\"')
			str = ft_strchr(str + 1, '\"');
		if (!str)
			return (0);
		if (*str == '\'')
			str = ft_strchr(str + 1, '\'');
		if (!str)
			return (0);
		str++;
	}
	return (1);
}

void	update(char *str, t_ast *ast, char **tmp)
{
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			exit(1);
		if (ft_strlen(str) > 0)
			add_history(str);
		if (!quotes_handler(str))
		{
			printf("quote_error\n");
			rl_replace_line("", 0);
			rl_redisplay();
			continue ;
		}
		str = split_to_tokens(str, &tmp);
		if (!tmp)
			continue ;
		ast = generate_ast(tmp);
		//DEBUG_MODE
		print_ast(ast, "", 0);
		// execute the AST
		// free the AST
		tmp = free_arr(tmp);
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*str;
	char	**tmp;
	t_ast	*ast;

	(void)ac;
	(void)av;
	(void)ev;
	str = NULL;
	tmp = NULL;
	ast = NULL;
	signal(SIGQUIT, SIG_IGN);
	update(str, ast, tmp);
	return (0);
}

// WARNING: potentially make
// The readline() function can cause memory leaks. You don’t have to fix them. But
// that doesn’t mean your own code, yes the code you wrote, can have memory
// leaks.