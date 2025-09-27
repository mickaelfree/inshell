/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:29:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/27 18:11:35 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>
#include <stdio.h>

void	print_custom_error(int err)
{
	if (err == ERR_ALLOC_ENV)
		printf(ERR_MSG_ALLOC ERR_MSG_ALLOC_ENV "\n");
	else if (err == ERR_ALLOC_EXPORT)
		printf(ERR_MSG_ALLOC ERR_MSG_ALLOC_EXPORT "\n");
	else if (err == ERR_ALLOC_UNSET)
		printf(ERR_MSG_ALLOC ERR_MSG_ALLOC_UNSET "\n");
	else if (err == ERR_ALLOC_PIPE_BUILD)
		printf(ERR_MSG_ALLOC ERR_MSG_ALLOC_PIPE_BUILD "\n");
	else if (err == ERR_ALLOC_PIPE_UTILS)
		printf(ERR_MSG_ALLOC ERR_MSG_ALLOC_PIPE_UTILS "\n");
	else
		printf(ERR_MESSAGE "%sUnknown error\n%s", RED, RESET);
}

int	print_error_and_ret(int err, int ret)
{
	print_custom_error(err);
	if (ret == 1)
		return (1);
	else
		return (NULL);
}
