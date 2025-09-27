/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:29:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 00:38:00 by zsonie           ###   ########lyon.fr   */
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

int	print_error_ret_err(int err)
{
	print_custom_error(err);
	return (1);
}

void	*print_error_ret_NULL(int err)
{
	print_custom_error(err);
	return (NULL);
}
