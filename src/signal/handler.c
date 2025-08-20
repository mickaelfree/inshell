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
        if(sig == SIGINT)
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

}

