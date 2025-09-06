/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:23:59 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/05 03:29:53 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"

static int count_pipe(t_ast *ast)
{
    if (!ast)
        return (0);
    
    int count = 0;
    
    if (ast->type == AST_PIPE)
        count = 1;
    count += count_pipe(ast->left);
    count += count_pipe(ast->right);
    
    return (count);
}

static void	exec_builtin_ast(t_ast *node, char ***ev)
{
	if (!node->left)
		node->exec(NULL, ev);
	else
		node->exec(node->left->token, ev);
}

void	execute_node(t_ast *node, char ***ev)
{
	if (ft_strncmp(node->token, "echo", 5) == 0)
		node->exec(node->left, NULL);
	else if (ft_strncmp(node->token, "cd", 3) == 0)
		exec_builtin_ast(node, ev);
	else if (ft_strncmp(node->token, "pwd", 4) == 0)
		node->exec(NULL, NULL);
	else if (ft_strncmp(node->token, "export", 7) == 0)
		exec_builtin_ast(node, ev);
	else if (ft_strncmp(node->token, "unset", 6) == 0)
		exec_builtin_ast(node, ev);
	else if (ft_strncmp(node->token, "env", 4) == 0)
		exec_builtin_ast(node, ev);
	else if (ft_strncmp(node->token, "exit", 5) == 0)
		exec_builtin_ast(node, ev);
	else
		printf("%s: command not found\n", node->token);
}

void	execute_ast(t_ast *ast, char ***ev)
{
	int pipe_count;

	if (!ast)
		return ;
	if (ast->type == AST_CMD)
		execute_node(ast, ev);
	else if (ast->type == AST_PIPE)
	{
		pipe_count = count_pipe(ast);
		// execute_ast_pipeline(ast, ev, pipe_count);
	}
	else if (ast->type == AST_WORD)
		execute(ast->token, ev);
	else
		printf("%s: command not found\n", ast->token);
}
