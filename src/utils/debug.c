/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:06:38 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/07 02:07:13 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

void	print_token(t_pre_token *token)
{
	char	*type_token[] = {"WORD", "SINGLE_QUOTE", "DOUBLE_QUOTE", "PIPE",
		"REDIR_IN", "REDIR_OUT", "HEREDOC", "APPEND"};
		
	printf("print_token called from: %p\n", __builtin_return_address(0));
	while (token)
	{
		printf("Token: %.*s (type: %s)\n", token->len, token->start,
			type_token[token->type]);
		token = token->next;
	}
}
