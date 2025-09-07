/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:00:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/07 02:06:56 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

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
	while (*ptr)
	{
		token_start = ptr;
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
			quote_state = 0;
			while (*ptr)
			{
				if (quote_state == 0 && (is_whitespace(*ptr)
						|| is_operator(*ptr)))
					break ;
				if (is_quote(*ptr) && quote_state == 0)
				{
					quote_char = *ptr;
					if (quote_char == '\'')
						quote_state = 1;
					else if (quote_char == '"')
						quote_state = 2;
					ptr++;
					continue ;
				}
				if (*ptr == quote_char && quote_state > 0)
				{
					quote_state = 0;
					ptr++;
					continue ;
				}
				ptr++;
			}
			if (quote_state > 0)
			{
				printf("Error: unclosed quote\n");
				free_token_list(head);
				return (NULL);
			}
			add_new_token(&head, &current, token_start, ptr - token_start,
				TOKEN_WORD);
		}
		skip_whitespace(&ptr);
	}
	return (head);
}
char	*remove_quotes(char *token, int len)
{
	char	*result;
	int		i = 0, j;
	int		in_single = 0, in_double;

	result = malloc(len + 1);
	i = 0, j = 0;
	in_single = 0, in_double = 0;
	while (i < len)
	{
		if (token[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++; // Skip the quote
		}
		else if (token[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++; // Skip the quote
		}
		else
		{
			result[j++] = token[i++];
		}
	}
	result[j] = '\0';
	return (result);
}
