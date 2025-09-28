/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:21:00 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 10:01:43 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

int	can_handle_pipe(t_pre_token *token)
{
	return (token->type == TOKEN_PIPE);
}

int	can_handle_redirection(t_pre_token *token)
{
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC);
}

int	can_handle_word(t_pre_token *token)
{
	return (token->type == TOKEN_WORD || token->type == TOKEN_QUOTED
		|| token->type == TOKEN_DOUBLE_QUOTE
		|| token->type == TOKEN_SINGLE_QUOTE);
}

int	can_handle_whitespace_quote(t_pre_token *token)
{
	return (token->type == TOKEN_WHITESPACE_QUOTE);
}
