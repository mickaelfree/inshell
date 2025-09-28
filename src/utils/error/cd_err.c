/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 01:50:20 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 02:52:14 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mandatoshell.h>
#include <unistd.h>

char	*cd_err(const char *msg, int status)
{
	write(STDERR_FILENO, msg, (int)ft_strlen(msg));
	g_last_exit_status = status;
	return (NULL);
}
