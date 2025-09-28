/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:00:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 11:56:15 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"
#include "ft_utils.h"
#include "is_char.h"
#include "mandatoshell.h"
#include <unistd.h>

static int	create_type_token(t_pre_token **head, t_pre_token **current,
		char **ptr)
{
	int	type;

	if (is_append(*ptr))
		type = TOKEN_APPEND;
	else if (is_heredoc(*ptr))
		type = TOKEN_HEREDOC;
	else if (*(*ptr) == '>')
		type = TOKEN_REDIR_OUT;
	else if (*(*ptr) == '<')
		type = TOKEN_REDIR_IN;
	else
		type = TOKEN_PIPE;
	if (!add_type_token(head, current, ptr, type))
	{
		ft_free_token_list(*head);
		return (0);
	}
	if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT)
		(*ptr)++;
	else
		(*ptr) += 2;
	skip_whitespace(ptr);
	return (1);
}

static int	is_only_whitespace_in_quotes(char *start, int len)
{
	int		i;
	int		in_quotes;
	char	quote_char;
	int		has_quotes;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	has_quotes = 0;
	while (i < len)
	{
		if (!in_quotes && is_quote(start[i]))
		{
			in_quotes = 1;
			quote_char = start[i];
			has_quotes = 1;
		}
		else if (in_quotes && start[i] == quote_char)
			in_quotes = 0;
		else if (in_quotes && !is_whitespace(start[i]))
			return (0);
		i++;
	}
	return (has_quotes);
}

static int	create_word_token(t_pre_token **head, t_pre_token **current,
		char **ptr, char **token_start)
{
	if (!check_for_quotes(head, ptr))
		return (0);
	if (is_only_whitespace_in_quotes(*token_start, *ptr - *token_start))
	{
		if (!add_whitespace_quote_token(head, current, *token_start, *ptr
				- *token_start))
		{
			ft_free_token_list(*head);
			return (0);
		}
	}
	else
	{
		if (!add_word_token(head, current, *token_start, *ptr - *token_start))
		{
			ft_free_token_list(*head);
			return (0);
		}
	}
	skip_whitespace(ptr);
	return (1);
}

t_pre_token	*identify_token(char *line)
{
	t_pre_token	*head;
	t_pre_token	*current;
	char		*ptr;
	char		*token_start;

	head = NULL;
	current = NULL;
	ptr = line;
	skip_whitespace(&ptr);
	while (*ptr)
	{
		token_start = ptr;
		if (is_pipe(*ptr) || is_redir(*ptr) || is_heredoc(ptr)
			|| is_append(ptr))
		{
			if (!create_type_token(&head, &current, &ptr))
				return (NULL);
		}
		else
		{
			if (!create_word_token(&head, &current, &ptr, &token_start))
				return (NULL);
		}
	}
	return (head);
}
