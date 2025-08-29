/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:01:51 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/30 00:47:54 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"

void	error_exit(void)
{
	if (errno == 2 || errno == 14)
	{
		if (errno == 2)
			ft_putstr_fd("No such file or directory\n", 2);
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
