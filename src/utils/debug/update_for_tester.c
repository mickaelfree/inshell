/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_for_tester.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 06:38:23 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 06:54:34 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <ft_structs.h>
#include <mandatoshell.h>
#include <libft.h>
#include <ft_utils.h>
#include <ft_parsing.h>
#include <readline/readline.h>
#include <readline/history.h>

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

static int	check_gnl(char **raw_line, char **line)
{
	*raw_line = get_next_line(fileno(stdin));
	if (!(*raw_line))
		return (0);
	*line = ft_strtrim(*raw_line, "\n");
	free(*raw_line);
	return (1);
}

static void	check_update(t_command **cmd, char *line, char ***new_env)
{
	*cmd = parse_token(line, *new_env);
	if (DEBUG_MODE)
		display_parsed_command(*cmd);
	if (*cmd)
		execute_cmd(*cmd, new_env);
	ft_free_commands(*cmd);
	free(line);
}

void	update_for_tester(char ***new_env)
{
	char		*line;
	t_command	*cmd;
	char		*raw_line;

	while (1)
	{
		if (isatty(fileno(stdin)))
		{
			line = readline("Mandatoshell>");
		}
		else
		{
			if (!check_gnl(&raw_line, &line))
				break ;
		}
		rl_check_and_exit(line, new_env);
		if (*line)
			add_history(line);
		else
		{
			free(line);
			continue ;
		}
		check_update(&cmd, line, new_env);
	}
}
