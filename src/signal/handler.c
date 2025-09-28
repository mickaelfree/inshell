/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:48:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 02:09:04 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	ft_handle_ctrld(void)
{
	printf("exit\n");
	rl_clear_history();
	exit(0);
}

void	ft_handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_last_exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (isatty(STDIN_FILENO))
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_last_exit_status = 131;
	}
}
