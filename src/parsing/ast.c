/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:16:12 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/31 00:48:40 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include <libft.h>

/**
 * @brief Helper function to insert a redirection or pipe node into the AST.
 *
 * If the current root node is a redirection:
 * - The first child is attached to `left`.
 * - The second child is attached to `right`.
 *
 * If the current root node is a pipe:
 * - If a right child already exists, the new node is attached to the left.
 * - Otherwise, the new node is attached to the right.
 *
 * @param res  Pointer to the current AST root.
 * @param node Node to insert.
 * @return Updated AST root after insertion.
 */
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

/**
 * @brief Recursively inserts a new node into the AST based on operator precedence.
 *
 * - If the tree is empty, the new node becomes the root.
 * - If the new node has higher type (precedence), it becomes the root,
 *   and the old root is attached as its right child.
 * - If node types are equal:
 *   - If `AST_PIPE` or `AST_END`, the new node replaces the old root.
 *   - Otherwise, the new node is inserted to the right recursively.
 * - If the new node has lower precedence, it is handled via @ref add_redir_or_pipe.
 *
 * @param tree Current AST root.
 * @param node Node to insert.
 * @return Updated AST root with the new node inserted.
 */
t_ast	*add_node_to_tree(t_ast *tree, t_ast *node)
{
	t_ast	*res;

	if (tree == NULL)
		return (node);
	res = tree;
	if (node->type > res->type)
	{
		node->right = res;
		res = node;
	}
	else if (node->type == res->type)
	{
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
		res = add_redir_or_pipe(res, node);
	}
	return (res);
}

/**
 * @brief Creates a new AST node from a given token.
 *
 * Identifies the node type based on the token:
 * - Redirection tokens ("<", "<<", ">", ">>") are classified as `AST_REDIRECT`.
 * - A pipe token ("|") is classified as `AST_PIPE`.
 * - Otherwise, the token is treated as a `AST_WORD`.
 *
 * The left and right pointers are initialized to NULL.
 *
 * @param token String representing the token.
 * @return Pointer to the newly created AST node.
 *         NULL if token is NULL or allocation fails.
 */
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

/**
 * @brief Generates an AST from a list of tokens.
 *
 * Iterates through the list of tokens, creates a new AST node for each,
 * and inserts it into the tree using @ref add_node_to_tree.
 *
 * Example:
 * - Tokens: ["ls", "-l", "|", "grep", "foo", ">", "out.txt", NULL]
 * - Produces a tree structure representing the command pipeline with redirection.
 *
 * @param tokens Null-terminated string array of tokens.
 * @return Pointer to the root of the constructed AST.
 */
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
