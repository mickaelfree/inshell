/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:48:37 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/20 19:37:21 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"

void	skip_whitespace(char **line)

{
	while (**line && is_whitespace((unsigned char)**line))
		(*line)++;
}
t_pre_token	*add_new_token(t_pre_token **head, t_pre_token **current,
		char *start, int len, int type, t_quote quote_state)
{
	t_pre_token	*new;

	new = malloc(sizeof(t_pre_token));
	if (!new)
		return (NULL);
	new->start = start;
	new->len = len;
	new->type = type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (new);
}

int	char_type(char *c)
{
	if (is_whitespace(*c))
		return (CHAR_WHITESPACE);
	else if (is_single_quote(*c))
		return (CHAR_SINGLE_QUOTE);
	else if (is_heredoc(c))
		return (CHAR_HEREDOC);
	else if (is_append(c))
		return (CHAR_APPEND);
	else if (is_double_quote(*c))
		return (CHAR_DOUBLE_QUOTE);
	else if (is_pipe(*c))
		return (CHAR_PIPE);
	else if (is_redir(*c))
		return (CHAR_REDIR);
	else if (is_escape(*c))
		return (CHAR_ESCAPE);
	else if (is_special(*c))
		return (CHAR_SPECIAL);
	else
		return (CHAR_NORMAL);
}
