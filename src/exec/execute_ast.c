/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:23:59 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/04 19:45:30 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

void	execute_node(t_ast *node, char ***ev, int *last_exit_status)
{
	(void)last_exit_status;
	if (!node)
		return ;
	if (node->type == AST_CMD)
	{
		if (ft_strncmp(node->token, "echo", 5) == 0)
			node->exec(node->left, NULL);
		else if (ft_strncmp(node->token, "cd", 3) == 0)
		{
			if (!node->left)
				node->exec(NULL, ev);
			else
				node->exec(node->left->token, ev);
		}
		else if (ft_strncmp(node->token, "pwd", 4) == 0)
			node->exec(NULL, NULL);
		else if (ft_strncmp(node->token, "export", 7) == 0)
		{
			if (!node->left)
				node->exec(NULL, ev);
			else
			{
				node->exec(node->left->token, ev);
				printf("=== AFTER builtin_export ===\n");
				int i = -1;
				while ((*ev)[++i])
				{
					if (strstr((*ev)[i], "TEST="))
						printf("Found: %s\n", (*ev)[i]);
				}
			}
		}
		else if (ft_strncmp(node->token, "unset", 6) == 0)
		{
			if (!node->left)
				node->exec(NULL, ev);
			else
				node->exec(node->left->token, ev);
		}
		else if (ft_strncmp(node->token, "env", 4) == 0)
		{
			if (!node->left)
				node->exec(NULL, ev);
			else
				node->exec(node->left->token, ev);
		}
		else if (ft_strncmp(node->token, "exit", 5) == 0)
		{
			if (!node->left)
				node->exec(NULL, ev);
			else
				node->exec(node->left->token, ev);
		}
		else
			printf("%s: command not found\n", node->token);
	}
	else if (node->type == AST_WORD)
		execute(node->token, ev);
	else
		printf("%s: command not found\n", node->token);
}

void	execute_ast(t_ast *ast, char ***ev, int *last_exit_status)
{
	(void)last_exit_status;
	if (!ast)
		return ;
	execute_node(ast, ev, last_exit_status);
	return ;
}
