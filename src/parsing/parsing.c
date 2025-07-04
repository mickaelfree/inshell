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

void free_token_list(t_pre_token *head)
{
    t_pre_token *current;
    t_pre_token *next;
    
    current = head;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
}
void process_simple_redirection(t_command *cmd, t_pre_token *token)
{
    t_pre_token *file_token;
    char *file_name;
    
    if (!token || !token->next)
        return;
    
    file_token = token->next;
    file_name = malloc(file_token->len + 1);
    if (!file_name)
        return;
    
    ft_strlcpy(file_name, file_token->start, file_token->len + 1);
    
    if (token->type == CHAR_REDIR)
    {
        if (token->start[0] == '<')
        {
            if (cmd->input_file)
                free(cmd->input_file);
            cmd->input_file = file_name;
        }
        else // '>'
        {
            if (cmd->output_file)
                free(cmd->output_file);
            cmd->output_file = file_name;
            cmd->append_mode = 0;
        }
    }
    else if (token->type == CHAR_APPEND)
    {
        if (cmd->output_file)
            free(cmd->output_file);
        cmd->output_file = file_name;
        cmd->append_mode = 1;
    }
    else if (token->type == CHAR_HEREDOC)
    {
        if (cmd->heredoc_delim)
            free(cmd->heredoc_delim);
        cmd->heredoc_delim = file_name;
    }
}

void add_simple_argument(t_command *cmd, t_pre_token *token)
{
    char *arg;
    char **new_args;
    int i;
    i =0;
    if (!token)
        return;
    
    // Allouer de la mémoire pour l'argument
    arg = malloc(token->len + 1);
    if (!arg)
        return;
    
    // Copier l'argument
    ft_strlcpy(arg, token->start, token->len + 1);
    
    // Réallouer le tableau d'arguments
    new_args = malloc(sizeof(char *) * (cmd->arg_count + 2));
    if (!new_args)
    {
        free(arg);
        return;
    }
    
    // Copier les arguments existants
    while ( i < cmd->arg_count)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    
    // Ajouter le nouvel argument
    new_args[cmd->arg_count] = arg;
    new_args[cmd->arg_count + 1] = NULL;
    
    // Libérer l'ancien tableau si nécessaire
    if (cmd->args)
        free(cmd->args);
    
    // Mettre à jour la commande
    cmd->args = new_args;
    cmd->arg_count++;
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
int check_quotes(t_pre_token *head)
{
    int single_quote_open = 0;
    int double_quote_open = 0;
    t_pre_token *current = head;
    
    while (current)
    {
        if (current->type == CHAR_SINGLE_QUOTE)
            single_quote_open = !single_quote_open;
        else if (current->type == CHAR_DOUBLE_QUOTE)
            double_quote_open = !double_quote_open;
        
        current = current->next;
    }
    
    if (single_quote_open || double_quote_open)
    {
        printf("Error: Unclosed quotes\n");
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
		//free_token_list(head);
		return (NULL);
	}
	
	// Créer une commande simple
	cmd = create_command(head);
	
	// Libérer la liste de tokens
	free_token_list(head);
	
	return (cmd);
}
