/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:25:37 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/03 23:22:15 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include <libft.h>

void	*set_exec_to_node(t_ast *node)
{
	if (!node)
		return (NULL);
	if (node->type == AST_CMD)
	{
		if (ft_strncmp(node->token, "echo", 5) == 0)
			return ((void *)&builtin_echo_ast);
		else if (ft_strncmp(node->token, "cd", 3) == 0)
			return ((void *)&builtin_cd);
		else if (ft_strncmp(node->token, "pwd", 4) == 0)
			return ((void *)&builtin_pwd);
		else if (ft_strncmp(node->token, "export", 7) == 0)
			return ((void *)&builtin_export);
		else if (ft_strncmp(node->token, "unset", 6) == 0)
			return ((void *)&builtin_unset);
		else if (ft_strncmp(node->token, "env", 4) == 0)
			return ((void *)&builtin_env);
		else if (ft_strncmp(node->token, "exit", 5) == 0)
			return ((void *)&builtin_exit);
	}
	return (NULL);
}

void    set_word_or_cmd_type(t_ast *node, int is_command_position)
{
    t_ast   *child;

    if (!node)
        return ;
    
    if (is_command_position && (ft_strncmp(node->token, "echo", 5) == 0 || 
        ft_strncmp(node->token, "cd", 3) == 0 || ft_strncmp(node->token, "pwd", 4) == 0
        || ft_strncmp(node->token, "export", 7) == 0 || ft_strncmp(node->token,
            "unset", 6) == 0 || ft_strncmp(node->token, "env", 4) == 0
        || ft_strncmp(node->token, "exit", 5) == 0))
    {
        node->type = AST_CMD;
        child = node->left;
        while (child)
        {
            set_word_or_cmd_type(child, 0);
            child = child->left;
        }
    }
    else
        node->type = AST_WORD;
}

void	set_command_arguments(t_ast *node)
{
	t_ast	*child;

	if (!node)
		return ;
	if (node->type == AST_CMD)
	{
		child = node->left;
		while (child)
		{
			if (child->type != AST_REDIRECT && child->type != AST_PIPE)
			{
				child->type = AST_WORD;
				child->exec = NULL;
			}
			child = child->left;
		}
	}
	set_command_arguments(node->left);
	set_command_arguments(node->right);
}

void	concatenate_argument_to_cmd(t_ast *cmd_node, char *new_arg)
{
	t_ast	*arg_node;
	char	*old_args;
	char	*new_args;
	char	*final_args;

	if (!cmd_node || cmd_node->type != AST_CMD)
		return ;
	if (!cmd_node->left)
	{
		arg_node = ft_calloc(sizeof(t_ast), 1);
		arg_node->type = AST_WORD;
		arg_node->token = ft_strdup(new_arg);
		cmd_node->left = arg_node;
	}
	else if (cmd_node->left->type == AST_WORD )
	{
		old_args = cmd_node->left->token;
		new_args = ft_strjoin(old_args, " ");
		final_args = ft_strjoin(new_args, new_arg);
		free(old_args);
		free(new_args);
		cmd_node->left->token = final_args;
	}
}

