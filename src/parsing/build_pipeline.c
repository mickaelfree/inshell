/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:12:14 by mickmart          #+#    #+#             */
/*   Updated: 2025/07/06 17:53:35 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

void init_command(t_command *cmd)
{
        cmd->args = NULL;
        cmd->input_file = NULL;
        cmd->output_file = NULL;
        cmd->heredoc_delim = NULL;
        cmd->append_mode = 0;
        cmd -> next = NULL;
}
int handle_redirection(t_command *cmd, t_pre_token **token)
{
    int type = (*token)->type;
    
    // Passer au token suivant (nom du fichier ou délimiteur)
    *token = (*token)->next;
    if (!*token || (*token)->type != TOKEN_WORD)
        return 0; // Erreur: pas de nom de fichier ou délimiteur
    
    char *value = strndup((*token)->start, (*token)->len);
    
    if (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN)
    {
        if (*((*token)->start - 1) == '<')
            cmd->input_file = value;
        else // '>'
        {
            cmd->output_file = value;
            cmd->append_mode = 0;
        }
    }
    else if (type == TOKEN_APPEND) // '>>'
    {
        cmd->output_file = value;
        cmd->append_mode = 1;
    }
    else if (type == TOKEN_HEREDOC) // '<<'
    {
        cmd->heredoc_delim = value;
    }
    
    return 1;
}
t_command *build_pipeline(t_pre_token *tokens)
{
    t_command *head = NULL;
    t_command *current = NULL;
    t_pre_token *token = tokens;
    
        while (token)
    {
        // Si c'est le début ou un pipe, créer une nouvelle commande
        if (!current || token->type == TOKEN_PIPE)
        {
            t_command *new_cmd = malloc(sizeof(t_command));
            if (!new_cmd)
                return NULL;
            init_command(new_cmd);
            
            // Ajouter au pipeline
            if (!head)
                head = new_cmd;
            else
                current->next = new_cmd;
            current = new_cmd;
            
            if (token->type == TOKEN_PIPE)
                token = token->next; // Passer le token de pipe
            continue;
        }
        
        // Traiter les redirections
        if (token->type >= TOKEN_REDIR_IN && token->type <= TOKEN_HEREDOC)
        {
            if (!handle_redirection(current, &token))
            {
                // Nettoyer et libérer la mémoire en cas d'erreur
                // (à implémenter plus tard)
                return NULL;
            }
            continue; // handle_redirection avance déjà le token
        }
        
        token = token->next;
    }
    return head;
}
