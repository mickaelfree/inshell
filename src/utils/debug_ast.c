/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:56:19 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/01 01:58:02 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"
#include <stdio.h>

const char	*get_exec_string(void (*exec)())
{
	if (exec == NULL)
		return ("NULL");
	else if (exec == &execute_cmd)
		return ("execute_cmd");
	else if (exec == &execute_builtin)
		return ("execute_builtin");
	else
		return ("UNKNOWN_FUNC");
}

const char	*get_type_string(int type)
{
	switch (type)
	{
	case AST_WORD:
		return ("WORD");
	case AST_PIPE:
		return ("PIPE");
	case AST_REDIRECT:
		return ("REDIRECT");
	case AST_END:
		return ("END");
	default:
		return ("UNKNOWN");
	}
}

void	print_ast(const t_ast *node, const char *prefix, int is_left)
{
	char	new_prefix[256];

	if (!node)
		return ;
	printf("%s", prefix);
	printf(is_left ? "├── " : "└── ");
	if (node->type == AST_WORD || node->type == AST_REDIRECT)
		printf("%s: %s Exec:%s\n", get_type_string(node->type), node->token, get_exec_string(node->exec));
	else
		printf("%s\n", get_type_string(node->type));
	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix,
		is_left ? "│   " : "    ");
	if (node->left && node->right)
	{
		print_ast(node->left, new_prefix, 1);
		print_ast(node->right, new_prefix, 0);
	}
	else if (node->left)
	{
		print_ast(node->left, new_prefix, 0);
	}
	else if (node->right)
	{
		print_ast(node->right, new_prefix, 0);
	}
}
