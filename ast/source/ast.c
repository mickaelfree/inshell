/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:16:12 by zsonie            #+#    #+#             */
/*   Updated: 2025/06/08 11:51:17 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"

t_ast	*add_redir_or_pipe(t_ast *res, t_ast *node)
{
	if (res->type == AST_REDIRECT)
	{
		if (res->left == NULL)
			res->left = add_node_to_tree(res->left, node);
		else
			res->right = add_node_to_tree(res->right, node);
	}
	if (res->type == AST_PIPE)
	{
		if (res->right != NULL)
			res->left = add_node_to_tree(res->left, node);
		else
			res->right = add_node_to_tree(res->right, node);
	}
	return (res);
}

t_ast	*add_node_to_tree(t_ast *tree, t_ast *node)
{
	t_ast	*res;

	if (tree == NULL)
		return (node);
	res = tree;
	if (node->type > res->type)
	{
		//add until AST_END because AST_END == 0
		node->right = res;
		res = node;
	}
	else if (node->type == res->type)
	{
		//if same type, check if type == AST_END of AST_PIPE
		//if not end or pipe then add again but starting from next node
		if (node->type == AST_PIPE || node->type == AST_END)
		{
			node->right = res;
			res = node;
		}
		else
			res->right = add_node_to_tree(res->right, node);
	}
	else
	{
		//if node->type < res->type then need to add left (if possible)
		res = add_redir_or_pipe(res, node);
	}
	return (res);
}

t_ast	*create_node(char *token)
{
	t_ast	*result;

	result = malloc(sizeof(t_ast));
	if (token == NULL)
		return (NULL);
	if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, ">>", 2) == 0 || \
    ft_strncmp(token, "<", 1) == 0 || ft_strncmp(token, "<<", 2) == 0)
	{
		result->type = AST_REDIRECT;
		//exec result->exec = ? ;
	}
	else if (ft_strncmp("|", token, 1) == 0)
	{
		result->type = AST_PIPE;
		//exec
	}
	else
	{
		result->type = AST_WORD;
		//exec
	}
	result->token = token;
	result->left = NULL;
	result->right = NULL;
	return (result);
}

t_ast	*generate_ast(char **tokens)
{
	t_ast	*result;
	t_ast	*node;

	result = NULL;
	while (*tokens != NULL)
	{
		node = create_node(*tokens);
		result = add_node_to_tree(result, node);
		tokens++;
	}
	return (result);
}
