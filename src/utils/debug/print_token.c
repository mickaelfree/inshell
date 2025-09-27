/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:31:22 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 00:32:39 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include<ft_structs.h>
#include<stdio.h>

void	print_token(t_pre_token *token)
{
	int	token_num;

	token_num = 0;
	printf("=== DEBUG TOKENS ===\n");
	while (token)
	{
		printf("Token %d: '%.*s' (type: %d, len: %d)\n", token_num, token->len,
			token->start, token->type, token->len);
		token = token->next;
		token_num++;
	}
	printf("=== END TOKENS ===\n");
}
