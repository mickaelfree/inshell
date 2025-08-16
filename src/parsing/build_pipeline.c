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
    cmd->arg_count = 0;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->heredoc_delim = NULL;
    cmd->append_mode = 0;
    cmd->next = NULL;
}

static void add_argument(t_command *cmd, char *value)
{
    char *expanded_value = expand_variables(value);
    if (!expanded_value)
        expanded_value = ft_strdup("");
    char **new_args = malloc(sizeof(char *) * (cmd->arg_count + 2));
    if (!new_args)
        return;

    int i = 0;
    while (i < cmd->arg_count)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[cmd->arg_count] = expanded_value;
    new_args[cmd->arg_count + 1] = NULL;

    if (cmd->args)
        free(cmd->args);
    cmd->args = new_args;
    cmd->arg_count++;
    free(value);
}

int handle_redirection(t_command *cmd, t_pre_token **token)
{
    int type = (*token)->type;
    *token = (*token)->next;
    if (!*token || ((*token)->type != TOKEN_WORD && (*token)->type != TOKEN_QUOTED))
    {
        printf("Syntax error: missing file after redirection\n");
        return 0;
    }

    char *value = strndup((*token)->start, (*token)->len);
    char *expanded_value = expand_variables(value);  // Expansion pour les redirections
    free(value);
    if (!expanded_value)
        expanded_value = ft_strdup("");

    if (type == TOKEN_REDIR_IN)
    {
        if (cmd->input_file)
        {
            printf("Warning: multiple input redirections, last wins\n");
            free(cmd->input_file);
        }
        cmd->input_file = expanded_value;
    }
    else if (type == TOKEN_REDIR_OUT || type == TOKEN_APPEND)
    {
        if (cmd->output_file)
        {
            printf("Warning: multiple output redirections, last wins\n");
            free(cmd->output_file);
        }
        cmd->output_file = expanded_value;
        cmd->append_mode = (type == TOKEN_APPEND) ? 1 : 0;
    }
    else if (type == TOKEN_HEREDOC)
    {
        if (cmd->heredoc_delim)
        {
            printf("Warning: multiple heredoc, last wins\n");
            free(cmd->heredoc_delim);
        }
        cmd->heredoc_delim = expanded_value;
    }
    else
        free(expanded_value);

    return 1;
}

t_command *build_pipeline(t_pre_token *tokens)
{
    t_command *head = NULL;
    t_command *current = NULL;
    t_pre_token *token = tokens;

    while (token)
    {
        if (!current || token->type == TOKEN_PIPE)
        {
            t_command *new_cmd = malloc(sizeof(t_command));
            if (!new_cmd)
                return NULL;
            init_command(new_cmd);

            if (!head)
                head = new_cmd;
            else
                current->next = new_cmd;
            current = new_cmd;

            if (token->type == TOKEN_PIPE)
            {
                token = token->next;
                if (!token)
                {
                    printf("Syntax error: pipe at end\n");
                    return NULL;
                }
            }
        }

        if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT ||
            token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
        {
            if (!handle_redirection(current, &token))
                return NULL;
            token = token->next;
            continue;
        }

        if (token->type == TOKEN_WORD || token->type == TOKEN_QUOTED)
        {
            char *value = strndup(token->start, token->len);
            add_argument(current, value);
        }

        token = token->next;
    }

    return head;
}
