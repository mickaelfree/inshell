/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:52:34 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/20 20:15:11 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"
void init_command(t_command *cmd)
{
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_mode = 0;
	cmd->heredoc_delim = NULL;
}
t_command *create_command(t_pre_token *tokens)
{
	t_pre_token *current;
	t_command *cmd;
	
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	
        init_command(cmd);
	current = tokens;
	while (current)
	{
		if (current->type == CHAR_REDIR || current->type == CHAR_APPEND || 
			current->type == CHAR_HEREDOC)
		{
			process_simple_redirection(cmd, current);
			current = current->next ? current->next->next : NULL;
			continue;
		}
		
		if (current->type == CHAR_NORMAL || 
			current->type == CHAR_SINGLE_QUOTE || 
			current->type == CHAR_DOUBLE_QUOTE)
		{
			add_simple_argument(cmd, current);
		}
		if (current)
			current = current->next;
	}
	return (cmd);
}
int	check_quotes(t_pre_token *head)
{
	int	quote_count;

	quote_count = 0;
	while (head)
	{
		if (head->type == CHAR_SINGLE_QUOTE || head->type == CHAR_DOUBLE_QUOTE)
			quote_count++;
		head = head->next;
	}
	if (quote_count % 2 != 0)
	{
		printf("Unmatched quotes");
		return (1);
	}
	return (0);
}

t_command *parse_token(char *line)
{
	t_pre_token	*head;
	t_command	*cmd;

	head = identify_token(line);
	if (!head)
		return (NULL);
	if (check_quotes(head))
	{
		free_token_list(head);
		return (NULL);
	}
	
	// Créer une commande simple
	cmd = create_command(head);
	
	// Libérer la liste de tokens
	free_token_list(head);
	
	return (cmd);
}
