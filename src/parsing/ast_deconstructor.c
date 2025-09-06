/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_deconstructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:51:27 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/05 03:30:00 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "libft.h"

static void collect_tokens_correct_order(t_ast *node, char ***args)
{
    if (!node)
        return;
    if (node->type == AST_PIPE)
    {
        collect_tokens_correct_order(node->right, args);
        if (node->token)
            add_elem_to_list(args, node->token);
        collect_tokens_correct_order(node->left, args);
    }
    else if (node->type == AST_REDIRECT)
    {
        collect_tokens_correct_order(node->right, args);
        if (node->token)
            add_elem_to_list(args, node->token);
        collect_tokens_correct_order(node->left, args);
    }
    else if (node->type == AST_CMD)
    {
        if (node->token)
            add_elem_to_list(args, node->token);
        collect_tokens_correct_order(node->left, args);
    }
    else if (node->type == AST_WORD)
    {
        if (node->token)
            add_elem_to_list(args, node->token);
        collect_tokens_correct_order(node->left, args);
    }
}

char **ast_to_args(t_ast *root)
{
    char **args = NULL;

    if (!root)
        return (NULL);

    collect_tokens_correct_order(root, &args);
    return (args);
}

void print_doublechar(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
}
