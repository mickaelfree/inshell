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

static char *type_token []= {"NORMAL","WHITESPACE","PIPE","REDIR","APPEND","HEREDOC","SINGLE_QUOTE","DOUBLE_QUOTE","ESCAPE","SPECIAL"};
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
void parse_quote(t_pre_token *token)
{
        int in_quote = 0;
        while (token)
        {
                if (token->type == TOKEN_QUOTED )
                {
                        printf("cococote \n");
                }
                printf("Token: %.*s (%s)\n", token->len, token->start, type_token[token->type]);
                token = token->next;
        }

}
void free_token_list(t_pre_token *head)
{
    t_pre_token *current = head;
    t_pre_token *next;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

void free_commands(t_command *head)
{
    t_command *current = head;
    t_command *next;
    int i;
    while (current)
    {
        next = current->next;
        if (current->args)
        {
            i = 0;
            while (i < current->arg_count)
                free(current->args[i]);
            free(current->args);
                        i++;
        }
        free(current->input_file);
        free(current->output_file);
        free(current->heredoc_delim);
        free(current);
        current = next;
    }
}

t_command *parse_token(char *line)
{
    t_pre_token *tokens = identify_token(line);
    if (!tokens)
        return NULL;

    print_token(tokens);

    t_command *commands = build_pipeline(tokens);

    free_token_list(tokens);

    return commands;
}
