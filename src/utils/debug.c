/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:06:38 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/24 03:40:27 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

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

void	display_parsed_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	printf("\n===== PARSING RESULT =====\n");
	printf("- Arguments (%d):\n", cmd->arg_count);
	i = -1;
	while (++i < cmd->arg_count)
		printf("  [%d]: '%s'\n", i, cmd->args[i]);
	if (cmd->input_file)
		printf("- Input redirection: '%s'\n", cmd->input_file);
	if (cmd->output_file)
		printf("- Output redirection: '%s' (append: %d)\n", cmd->output_file,
			cmd->append_mode);
	if (cmd->heredoc_delim)
		printf("- Heredoc delimiter: '%s'\n", cmd->heredoc_delim);
	printf("==========================\n\n");
}
