/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:25:37 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/02 05:40:22 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include <libft.h>

void	*set_exec_to_node(t_ast *node)
{
	if (!node)
		return NULL;
	if (node->type == AST_CMD)
	{
		if (ft_strncmp(node->token, "echo", 5) == 0)
			return (void *)&builtin_echo_ast;
		else if (ft_strncmp(node->token, "cd", 3) == 0)
			return (void *)&builtin_cd;
		else if (ft_strncmp(node->token, "pwd", 4) == 0)
			return (void *)&builtin_pwd;
		else if (ft_strncmp(node->token, "export", 7) == 0)
			return (void *)&builtin_export;
		else if (ft_strncmp(node->token, "unset", 6) == 0)
			return (void *)&builtin_unset;
		else if (ft_strncmp(node->token, "env", 4) == 0)
			return (void *)&builtin_env;
		else if (ft_strncmp(node->token, "exit", 5) == 0)
			return (void *)&builtin_exit;
	}
	return NULL;
}

void		set_word_or_cmd_type(t_ast *node)
{
	if (!node)
		return;
	if (ft_strncmp(node->token, "echo", 5) == 0 || ft_strncmp(node->token, "cd",
			3) == 0 || ft_strncmp(node->token, "pwd", 4) == 0
		|| ft_strncmp(node->token, "export", 7) == 0 || ft_strncmp(node->token,
			"unset", 6) == 0 || ft_strncmp(node->token, "env", 4) == 0
		|| ft_strncmp(node->token, "exit", 5) == 0)
		{
			t_ast *child = node->left;
        	while (child)
        	{
        	    child->type = AST_WORD;
        	    child = child->left;
        	}
			node->type = AST_CMD;
		}
	else
		node->type = AST_WORD;
}

void set_command_arguments(t_ast *node)
{
    if (!node)
        return;
        
    if (node->type == AST_CMD)
    {
        t_ast *child = node->left;
        while (child)
        {
            if (child->type != AST_REDIRECT && child->type != AST_PIPE)
			{
                child->type = AST_WORD;
				child->exec = NULL;
			}
            child = child->left; // or whatever traversal method you use
        }
    }
    
    // Recursively process the entire tree
    set_command_arguments(node->left);
    set_command_arguments(node->right);
}

