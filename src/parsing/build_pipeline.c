/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:12:14 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 00:28:25 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"
#include "error.h"
#include "ft_parsing.h"
#include "utils.h"

void	init_command(t_command *cmd)
{
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_delim = NULL;
	cmd->append_mode = 0;
	cmd->redirections = NULL;
	cmd->next = NULL;
}

void	add_argument(t_command *cmd, char *value, char **envp)
{
	char	*expanded_value;
	char	**new_args;
	int		i;

	expanded_value = expand_variables_with_quote(value, envp);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	new_args = malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
	{
		print_custom_error(ERR_ALLOC_PIPE_BUILD);
		free(expanded_value);
		free(value);
		return ;
	}
	i = -1;
	while (++i < cmd->arg_count)
		new_args[i] = cmd->args[i];
	new_args[cmd->arg_count] = expanded_value;
	new_args[cmd->arg_count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->arg_count++;
	free(value);
}

t_command	*build_pipeline(t_pre_token *tokens, char **envp)
{
	t_command	*head;
	t_command	*current;
	t_pre_token	*token;

	head = NULL;
	current = NULL;
	token = tokens;
	while (token)
	{
		if (!current)
		{
			current = malloc(sizeof(t_command));
			if (!current)
				return (NULL);
			init_command(current);
			head = current;
		}
		if (!process_token(&token, &current, &head, envp))
		{
			ft_free_commands(head);
			return (NULL);
		}
	}
	return (head);
}
