/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:23:59 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/02 05:41:56 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

void execute_node(t_ast *node,char **ev, int *last_exit_status)
{
	(void)last_exit_status;
	if (!node)
		return;
	if (node->type == AST_CMD)
	{
		if (ft_strncmp(node->token, "echo", 5) == 0)
			builtin_echo_ast(node->left); // Placeholder for actual args and envp
		else if (ft_strncmp(node->token, "cd", 3) == 0)
			builtin_cd(NULL, &ev); // Placeholder for actual args and envp
		else if (ft_strncmp(node->token, "pwd", 4) == 0)
			builtin_pwd(NULL, NULL); // Placeholder for actual args and envp
		else if (ft_strncmp(node->token, "export", 7) == 0)
			builtin_export(NULL, NULL); // Placeholder for actual args and envp
		else if (ft_strncmp(node->token, "unset", 6) == 0)
			builtin_unset(NULL, NULL); // Placeholder for actual args and envp
		else if (ft_strncmp(node->token, "env", 4) == 0)
			builtin_env(NULL, &ev); // Placeholder for actual envp
		else if (ft_strncmp(node->token, "exit", 5) == 0)
			builtin_exit(NULL, &ev); // Placeholder for actual args
	}
	else
		printf("%s: command not found\n", node->token);
}

void execute_ast(t_ast *ast,char **ev, int *last_exit_status)
{
	(void)last_exit_status;
	if (!ast)
		return;
	execute_node(ast, ev, last_exit_status); // Placeholder for actual envp
	// Implementation of AST execution logic goes here
	// This typically involves traversing the AST and executing commands
	// according to their types (e.g., handling pipes, redirections, etc.)
	return;
}

