/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:28:05 by dedme             #+#    #+#             */
/*   Updated: 2025/07/30 07:28:28 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

void	ft_handle_ctrld(void)
{
	printf("exit\n");
	// free function that doesn't already exist
	exit(0);
}
void	ft_handle_sig(int sig)
{
	if (isatty(STDIN_FILENO) == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("kill the child\n");
		// need to keep pid somewhere in the struct
	}
}
