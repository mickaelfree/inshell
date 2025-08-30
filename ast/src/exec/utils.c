/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:57:24 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/30 23:22:40 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

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

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
