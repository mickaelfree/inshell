/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/06 20:46:24 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

int		g_last_exit_status = 0;
void	display_parsed_command(t_command *cmd)
{
	if (!cmd)
		return ;
	printf("\n===== PARSING RESULT =====\n");
	printf("- Arguments (%d):\n", cmd->arg_count);
	for (int i = 0; i < cmd->arg_count; i++)
		printf("  [%d]: '%s'\n", i, cmd->args[i]);
	if (cmd->input_file)
		printf("- Input redirection: '%s'\n", cmd->input_file);
	if (cmd->output_file)
		printf("- Output redirection: '%s' (append: %d)\n", cmd->output_file,
			cmd->append_mode);
	if (cmd->heredoc_delim)
		printf("- Heredoc delimiter: '%s'\n", cmd->heredoc_delim);
	printf("==========================\n\n");
}
void	test_parsing(void)
{
	char		*line;
	t_command	*cmds;
	t_command	*cur;

	line = "ls -l | grep \"test file\" > output.txt >> append.txt << END";
	cmds = parse_token(line, NULL);
	if (!cmds)
		return ;
	cur = cmds;
	while (cur)
	{
		printf("Command args: ");
		for (int i = 0; i < cur->arg_count; i++)
			printf("%s ", cur->args[i]);
		printf("\nInput: %s\nOutput: %s (append: %d)\nHeredoc: %s\n---\n",
			cur->input_file, cur->output_file, cur->append_mode,
			cur->heredoc_delim);
		cur = cur->next;
	}
	// ft_free_commands(cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**new_env;
	t_command	*cmd;
	int			builtin_ret;

	(void) argc;
	(void) argv;
	builtin_ret = 0;
	new_env = init_env(&envp);
	signal(SIGINT, ft_handle_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("Mandatoshell>");
		if (!line)
			ft_handle_ctrld();
		if (*line)
			add_history(line);
		else
		{
			free(line);
			continue ;
		}
		cmd = parse_token(line, new_env);

		if (cmd)
		{
			execute_cmd(cmd, &new_env);
		}
		ft_free_commands(cmd);
                free(line);
	}
	if (new_env)
		free(new_env);
	return (0);

}
