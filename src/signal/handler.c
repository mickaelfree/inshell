/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:48:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/03 17:49:09 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "inshell.h"


//TODO: Basically everything...
//check for pid to handle signals in child process and block in parent

// void	ft_handle_ctrld(void)
// {
// 	printf("exit\n");
// 	// free function that doesn't already exist
// 	exit(0);
// }
// void	ft_handle_sig(int sig)
// {
//         if(sig == SIGINT)
//         {
//                 if (isatty(STDIN_FILENO))
//                 {        
//                 	write(STDOUT_FILENO, "\n", 1);
//                 	rl_replace_line("", 0);
//                 	rl_on_new_line();
//                 	rl_redisplay();
//                 }
//                 g_last_exit_status = 130;
//         }

// }
