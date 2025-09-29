/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:21:00 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 20:07:13 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_structs.h>

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
