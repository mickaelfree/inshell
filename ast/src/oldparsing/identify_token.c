/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:00:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/30 23:13:54 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"

static char	*type_token[] = {"WORD", "QUOTED", "PIPE", "REDIR_IN", "REDIR_OUT",
		"HEREDOC", "APPEND"};

t_pre_token	*identify_token(char *line)
{
	t_pre_token	*head;
	t_pre_token	*current;
	char		*ptr;
	char		*token_start;
	int			quote_state;
	char		quote_char;
	int			type;

	head = NULL;
	current = NULL;
	ptr = line;
	quote_state = 0;
	quote_char = 0;
	skip_whitespace(&ptr);
        //TODO: gere les single quote et double quote directement avec les cote state
	while (*ptr)
	{
		token_start = ptr;
		if (is_quote(*ptr) && quote_state == 0)
		{
			quote_char = *ptr;
			if (quote_char == '\'')
				quote_state = 1;
			else if (quote_char == '"')
				quote_state = 2;
			ptr++;
			token_start = ptr;
			while (*ptr && *ptr != quote_char)
				ptr++;
			if (*ptr == quote_char)
			{
				add_new_token(&head, &current, token_start, ptr - token_start,
					TOKEN_QUOTED);
				ptr++;
				quote_state = 0;
			}
			else
			{
				printf("Error: unclosed quote\n");
				free_token_list(head);
				return (NULL);
			}
			skip_whitespace(&ptr);
			continue ;
		}
		if (is_pipe(*ptr))
		{
			add_new_token(&head, &current, ptr, 1, TOKEN_PIPE);
			ptr++;
		}
		else if (is_heredoc(ptr))
		{
			add_new_token(&head, &current, ptr, 2, TOKEN_HEREDOC);
			ptr += 2;
		}
		else if (is_append(ptr))
		{
			add_new_token(&head, &current, ptr, 2, TOKEN_APPEND);
			ptr += 2;
		}
		else if (is_redir(*ptr))
		{
			type = (*ptr == '<') ? TOKEN_REDIR_IN : TOKEN_REDIR_OUT;
			add_new_token(&head, &current, ptr, 1, type);
			ptr++;
		}
		else
		{
			while (*ptr && !is_whitespace(*ptr) && !is_operator(*ptr)
				&& !is_quote(*ptr))
				ptr++;
			add_new_token(&head, &current, token_start, ptr - token_start,
				TOKEN_WORD);
		}
		skip_whitespace(&ptr);
	}
	return (head);
}

void	print_token(t_pre_token *token)
{
	printf("print_token called from: %p\n", __builtin_return_address(0));
	while (token)
	{
		printf("Token: %.*s (type: %s)\n", token->len, token->start,
			type_token[token->type]);
		token = token->next;
	}
}
