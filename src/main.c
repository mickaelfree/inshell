/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 07:10:55 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <mandatoshell.h>
#include <ft_structs.h>
#include <ft_enum.h>
#include <ft_builtins.h>
#include <ft_parsing.h>
#include <ft_signal.h>
#include <signal.h>
#include <ft_utils.h>
#include <readline/history.h>
#include <readline/readline.h>

int			g_last_exit_status = 0;

static void	rl_check_and_exit(char *line, char ***new_env)
{
	if (!line)
	{
		printf("exit\n");
		rl_clear_history();
		if (*new_env)
			ft_free_env(*new_env);
		exit(0);
	}
}

void	update(char ***new_env)
{
	char		*line;
	t_command	*cmd;

	while (1)
	{
		line = readline("Mandatoshell>");
		rl_check_and_exit(line, new_env);
		if (*line)
			add_history(line);
		else
		{
			free(line);
			continue ;
		}
		cmd = parse_token(line, *new_env);
		if (DEBUG_MODE)
			display_parsed_command(cmd);
		if (cmd)
			execute_cmd(cmd, new_env);
		ft_free_commands(cmd);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**new_env;

	(void)argc;
	(void)argv;
	new_env = init_env(&envp);
	if (!new_env)
		return (g_last_exit_status);
	signal(SIGINT, ft_handle_sig);
	signal(SIGQUIT, ft_handle_sig);
	if (!TESTER)
		update(&new_env);
	else
		update_for_tester(&new_env);
	rl_clear_history();
	if (new_env)
		ft_free_env(new_env);
	return (g_last_exit_status);
}
