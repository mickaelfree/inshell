/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:56:19 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/02 00:19:06 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"
#include <stdio.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

const char	*get_exec_string(void (*exec)())
{
	if (exec == NULL)
		return ("NULL");
	else if (exec == (void *)&builtin_echo_ast)
		return ("builtin_echo_ast");
	else if (exec == (void *)&builtin_cd)
		return ("builtin_cd");
	else if (exec == (void *)&builtin_pwd)
		return ("builtin_pwd");
	else if (exec == (void *)&builtin_export)
		return ("builtin_export");
	else if (exec == (void *)&builtin_unset)
		return ("builtin_unset");
	else if (exec == (void *)&builtin_env)
		return ("builtin_env");
	else if (exec == (void *)&builtin_exit)
		return ("builtin_exit");
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
	case AST_CMD:
		return ("CMD");
	default:
		return ("UNKNOWN");
	}
}

void	print_ast(const t_ast *node, const char *prefix, int is_left)
{
    char	new_prefix[256];
    if (!node) {
        printf("DEBUG: Node is NULL\n");
        return ;
    }
	printf("%s%s", YELLOW,prefix);
	printf(is_left ? "├── " : "└── ");
	if (node->type == AST_WORD || node->type == AST_REDIRECT || node->type == AST_CMD)
		printf("%s%s: %s%s %sRelatedExec:%s%s\n", GREEN, get_type_string(node->type), RESET, node->token, CYAN,get_exec_string(node->exec), RESET);
	else
		printf("%s\n", get_type_string(node->type));
	snprintf(new_prefix, sizeof(new_prefix), "%s%s%s", YELLOW,prefix,
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

void print_cmd(t_command *cmd)
{
	int i;

	while (cmd)
	{
		printf("%sCommand:%s\n", BLUE, RESET);
		if (cmd->args)
		{
			printf("  %sArguments:%s\n", MAGENTA, RESET);
			for (i = 0; i < cmd->arg_count; i++)
			{
				printf("    [%d]: %s\n", i, cmd->args[i]);
			}
		}
		else
		{
			printf("  %sArguments: NULL%s\n", MAGENTA, RESET);
		}
		if (cmd->input_file)
			printf("  %sInput File:%s %s\n", CYAN, RESET, cmd->input_file);
		else
			printf("  %sInput File:%s NULL\n", CYAN, RESET);
		if (cmd->output_file)
			printf("  %sOutput File:%s %s\n", CYAN, RESET, cmd->output_file);
		else
			printf("  %sOutput File:%s NULL\n", CYAN, RESET);
		if (cmd->heredoc_delim)
			printf("  %sHeredoc Delimiter:%s %s\n", CYAN, RESET, cmd->heredoc_delim);
		else
			printf("  %sHeredoc Delimiter:%s NULL\n", CYAN, RESET);
		printf("  %sAppend Mode:%s %d\n", CYAN, RESET, cmd->append_mode);
		cmd = cmd->next;
	}
}
