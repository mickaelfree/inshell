/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_parsed_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:33:04 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 02:51:58 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_structs.h>
#include <stdio.h>

void	display_parsed_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	printf("\n===== PARSING RESULT =====\n");
	printf("- Arguments (%d):\n", cmd->arg_count);
	i = -1;
	while (++i < cmd->arg_count)
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
