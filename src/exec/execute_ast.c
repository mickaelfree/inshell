/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:23:59 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/04 22:39:54 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "libft.h"

static void	exec_builtin(t_ast *node, char ***ev)
{
	if (!node->left)
		node->exec(NULL, ev);
	else
		node->exec(node->left->token, ev);
}

void	execute_node(t_ast *node, char ***ev)
{
	if (!node)
		return ;
	if (node->type == AST_CMD)
	{
		if (ft_strncmp(node->token, "echo", 5) == 0)
			node->exec(node->left, NULL);
		else if (ft_strncmp(node->token, "cd", 3) == 0)
			exec_builtin(node, ev);
		else if (ft_strncmp(node->token, "pwd", 4) == 0)
			node->exec(NULL, NULL);
		else if (ft_strncmp(node->token, "export", 7) == 0)
			exec_builtin(node, ev);
		else if (ft_strncmp(node->token, "unset", 6) == 0)
			exec_builtin(node, ev);
		else if (ft_strncmp(node->token, "env", 4) == 0)
			exec_builtin(node, ev);
		else if (ft_strncmp(node->token, "exit", 5) == 0)
			exec_builtin(node, ev);
		else
			printf("%s: command not found\n", node->token);
	}
	else if (node->type == AST_WORD)
		execute(node->token, ev);
	else
		printf("%s: command not found\n", node->token);
}

void	execute_ast(t_ast *ast, char ***ev)
{
	if (!ast)
		return ;
	execute_node(ast, ev);
	return ;
}
