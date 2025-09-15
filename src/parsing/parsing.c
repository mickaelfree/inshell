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
