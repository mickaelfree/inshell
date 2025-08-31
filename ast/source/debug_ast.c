/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:56:19 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/30 00:47:50 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"
#include <stdio.h>

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
	// Draw tree branch
	printf("%s", prefix);
	printf(is_left ? "├── " : "└── ");
	// Print current node
	if (node->type == AST_WORD || node->type == AST_REDIRECT)
		printf("%s: %s\n", get_type_string(node->type), node->token);
	else
		printf("%s\n", get_type_string(node->type));
	// Prepare next prefix
	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix,
		is_left ? "│   " : "    ");
	// If both children exist, left is printed first with is_left=1
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
