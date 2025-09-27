/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 00:28:42 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_structs.h"
#include "ft_enum.h"
#include "mandatoshell.h"
#include "ft_signal.h"
#include "builtins.h"
#include "ft_parsing.h"
#include "libft.h"
#include "utils.h"

int			g_last_exit_status = 0;

// static void	test_parsing(void)
// {
// 	char		*line;
// 	t_command	*cmds;
// 	t_command	*cur;
// 	int			i;

// 	line = "ls -l | grep \"test file\" > output.txt >> append.txt << END";
// 	cmds = parse_token(line, NULL);
// 	if (!cmds)
// 		return ;
// 	cur = cmds;
// 	while (cur)
// 	{
// 		printf("Command args: ");
// 		i = -1;
// 		while (++i < cur->arg_count)
// 			printf("%s ", cur->args[i]);
// 		printf("\nInput: %s\nOutput: %s (append: %d)\nHeredoc: %s\n---\n",
// 			cur->input_file, cur->output_file, cur->append_mode,
// 			cur->heredoc_delim);
// 		cur = cur->next;
// 	}
// 	if (cmds)
// 		ft_free_commands(cmds);
// }

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

//PLS REMOVE BEFORE LAST PUSH
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
			raw_line = get_next_line(fileno(stdin));
			if (!raw_line)
				break ;
			line = ft_strtrim(raw_line, "\n");
			free(raw_line);
		}
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
	//REMOVE BEFORE LAST PUSH
	if (!TESTER)
		update(&new_env);
	else
		update_for_tester(&new_env);
	rl_clear_history();
	if (new_env)
		ft_free_env(new_env);
	return (g_last_exit_status);
}
