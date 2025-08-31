/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:01:51 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/31 00:50:15 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

void	error_exit(void)
{
	if (errno == 2 || errno == 14)
	{
		if (errno == 2)
			ft_putstr_fd(" No such file or directory\n", 2);
		if (errno == 14)
			ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	if (errno == 13)
	{
		ft_putstr_fd("Permission denied\n", 2);
		exit(126);
	}
}


void    ft_error(char *msg)
{
    write(STDERR_FILENO, msg, ft_strlen(msg));
    write(STDERR_FILENO, "\n", 1);

    if (strstr(msg, " No such file or directory"))
    {
        g_last_exit_status = 127;
        exit(127);
    }
    if (strstr(msg, "Permission denied"))
    {
        g_last_exit_status = 126;
        exit(126);
    }
    g_last_exit_status = 1;
    exit(1);
}