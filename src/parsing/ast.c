/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:16:12 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/04 22:01:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
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
	else if (res->type == AST_PIPE)
	{
		if (res->right != NULL)
			res->left = add_node_to_tree(res->left, node);
		else
			res->right = add_node_to_tree(res->right, node);
	}
	else if (res->type == AST_CMD && node->type == AST_WORD)
		return (res);
	else if (res->type == AST_CMD)
	{
		res->left = add_node_to_tree(res->left, node);
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
 * - If the new node has lower precedence,
	it is handled via @ref add_redir_or_pipe.
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
			res->left = add_node_to_tree(res->left, node);
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

	result = ft_calloc(sizeof(t_ast), 1);
	if (!result)
		return (NULL);
	result->token = token;
	if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, ">>", 2) == 0
		|| ft_strncmp(token, "<", 1) == 0 || ft_strncmp(token, "<<", 2) == 0)
	{
		result->type = AST_REDIRECT;
	}
	else if (ft_strncmp("|", token, 1) == 0)
	{
		result->type = AST_PIPE;
	}
	else
	{
		clear_token_quotes(&result->token);
		result->type = AST_WORD;
		result->exec = NULL;
	}
	result->left = NULL;
	result->right = NULL;
	return (result);
}

// Helper function
static int	is_builtin_command(char *token)
{
	return (ft_strncmp(token, "echo", 4) == 0 || ft_strncmp(token, "cd", 3) == 0
		|| ft_strncmp(token, "pwd", 4) == 0 || ft_strncmp(token, "export",
			7) == 0 || ft_strncmp(token, "unset", 6) == 0 || ft_strncmp(token,
			"env", 4) == 0 || ft_strncmp(token, "exit", 5) == 0);
}

static void	set_exec_functions_recursively(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == AST_CMD)
		node->exec = set_exec_to_node(node);
	else
		node->exec = NULL;
	set_exec_functions_recursively(node->left);
	set_exec_functions_recursively(node->right);
}
/**
 * @brief Generates an AST from a list of tokens.
 *
 * Iterates through the list of tokens, creates a new AST node for each,
 * and inserts it into the tree using @ref add_node_to_tree.
 *
 * Example:
 * - Tokens: ["ls", "-l", "|", "grep", "foo", ">", "out.txt", NULL]
 *
	- Produces a tree structure representing the command pipeline with redirection.
 *
 * @param tokens Null-terminated string array of tokens.
 * @return Pointer to the root of the constructed AST.
 */
t_ast	*generate_ast(char **tokens)
{
	t_ast	*result;
	t_ast	*node;
	t_ast	*current_cmd;

	result = NULL;
	current_cmd = NULL;
	while (*tokens != NULL)
	{
		node = create_node(*tokens);
		if (!current_cmd && is_builtin_command(node->token))
		{
			node->type = AST_CMD;
			current_cmd = node;
			result = add_node_to_tree(result, node);
		}
		else if (current_cmd && (node->type == AST_WORD))
		{
			concatenate_argument_to_cmd(current_cmd, node->token);
			free(node->token);
			free(node);
		}
		else
		{
			current_cmd = NULL;
			result = add_node_to_tree(result, node);
		}
		tokens++;
	}
	set_exec_functions_recursively(result);
	return (result);
}
