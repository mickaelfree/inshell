/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 09:58:28 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 11:59:00 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"
#include "libft.h"
#include <stdio.h>

int	process_token(t_pre_token **token, t_command **current, t_command **head,
		char **envp)
{
	t_token_handler	handlers[5];
	int				i;

	init_handlers(handlers);
	i = 0;
	while (handlers[i].can_handle)
	{
		if (handlers[i].can_handle(*token))
			return (handlers[i].handle(current, token, envp, head));
		i++;
	}
	return (0);
}
