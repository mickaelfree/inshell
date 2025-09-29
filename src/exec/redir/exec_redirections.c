/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:28:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 19:58:54 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <mandatoshell.h>

static int	apply_redirection(t_redirection *r)
{
	t_redir_entry	func[NB_REDIRS_FUNC];
	int				i;

	init_redir_table(func);
	if (r->type == TOKEN_APPEND)
		r->append_mode = 1;
	i = 0;
	while (i < NB_REDIRS_FUNC)
	{
		if (func[i].type == r->type || (r->type == TOKEN_APPEND
				&& func[i].type == TOKEN_REDIR_OUT))
		{
			return (func[i].fn(r));
		}
		i++;
	}
	return (1);
}

int	exec_redirections(t_command *cmd)
{
	t_redirection	*rd;

	rd = cmd->redirections;
	while (rd)
	{
		if (!apply_redirection(rd))
			return (0);
		rd = rd->next;
	}
	return (1);
}
