/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:01:51 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/20 01:40:02 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
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
	exit(1);
}

void	ft_error(char *msg)
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
void	export_error(char *arg)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	g_last_exit_status = 1;
}
char	*cd_err(const char *msg, int status)
{
	write(STDERR_FILENO, msg, (int)ft_strlen(msg));
        g_last_exit_status = status;
	return (NULL);
}
