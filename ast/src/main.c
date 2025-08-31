/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:33:13 by jureix-c          #+#    #+#             */
/*   Updated: 2025/08/31 04:39:46 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

int		g_last_exit_status = 0;
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

void	update(char *str, t_ast *ast, char **tmp, int debug_mode)
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
			continue;
		}
		str = split_to_tokens(str, &tmp);
		if (!tmp)
			continue ;
		ast = generate_ast(tmp);
		if (debug_mode)
			print_ast(ast, "", 0);
		// execute the AST
		// free the AST
		ft_free(tmp);
	}
}


int	main(int ac, char **av, char **ev)
{
	char	*str;
	char	**tmp;
	t_ast	*ast;
	int		debug_mode;
	char	**new_env;

	(void)ac;
	(void)av;
	new_env = ft_env(ev);
	debug_mode = 1; // set to 1 to enable debug mode, 0 to disable
	str = NULL;
	tmp = NULL;
	ast = NULL;
	signal(SIGQUIT, SIG_IGN);
	update(str, ast, tmp, debug_mode);
	return (0);
}

// WARNING: potentially make
// The readline() function can cause memory leaks. You don’t have to fix them. But
// that doesn’t mean your own code, yes the code you wrote, can have memory
// leaks.