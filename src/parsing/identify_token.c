/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:00:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 02:06:41 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "ft_parsing.h"
#include "is_char.h"
#include "utils.h"
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

static int	create_word_token(t_pre_token **head, t_pre_token **current,
		char **ptr, char **token_start)
{
	if (!check_for_quotes(head, ptr))
		return (0);
	if (!add_word_token(head, current, *token_start, *ptr - *token_start))
	{
		ft_free_token_list(*head);
		return (0);
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
