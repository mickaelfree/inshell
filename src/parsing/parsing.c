/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:52:34 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/07 01:50:21 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

int	check_quotes(t_pre_token *head)
{
	int			single_quote_open;
	int			double_quote_open;
	t_pre_token	*current;

	single_quote_open = 0;
	double_quote_open = 0;
	current = head;
	while (current)
	{
		if (current->type == CHAR_SINGLE_QUOTE)
			single_quote_open = !single_quote_open;
		else if (current->type == CHAR_DOUBLE_QUOTE)
			double_quote_open = !double_quote_open;
		current = current->next;
	}
	if (single_quote_open || double_quote_open)
	{
		printf("Error: Unclosed quotes\n");
		return (1);
	}
	return (0);
}

t_command	*parse_token(char *line, char **envp)
{
	t_pre_token	*tokens;
	t_command	*commands;

	tokens = identify_token(line);
	if (!tokens)
		return (NULL);
	if (DEBUG_MODE)
		print_token(tokens);
	commands = build_pipeline(tokens, envp);
	free_token_list(tokens);
	return (commands);
}
