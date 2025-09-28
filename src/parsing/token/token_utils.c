/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:48:37 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/24 04:38:56 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"

t_pre_token	*add_type_token(t_pre_token **head, t_pre_token **current,
		char **start, int type)
{
	t_pre_token	*new;
	int			new_len;

	if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT)
		new_len = 1;
	else if (type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		new_len = 2;
	else
		return (NULL);
	new = malloc(sizeof(t_pre_token));
	if (!new)
		return (NULL);
	new->start = (*start);
	new->len = new_len;
	new->type = type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (new);
}

t_pre_token	*add_word_token(t_pre_token **head, t_pre_token **current,
		char *start, int len)
{
	t_pre_token	*new;

	new = malloc(sizeof(t_pre_token));
	if (!new)
		return (NULL);
	new->start = start;
	new->len = len;
	new->type = TOKEN_WORD;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (new);
}
