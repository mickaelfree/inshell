/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indentyfy_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:00:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/20 19:51:54 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"
//INFO:
//separer en fonction des etats 
//double quote = tant que je trouve pas de nouvel " jidentifie tout comme quoted 
//operateur separer la commande 
static char *type_token[] = {"WORD", "QUOTED", "PIPE", "REDIR_IN", "REDIR_OUT", "HEREDOC", "APPEND", "UNKNOWN"};

t_pre_token *identify_token(char *line)
{
    t_pre_token *head = NULL;
    t_pre_token *current = NULL;
    char *ptr = line;
    char *token_start = NULL;
    int type;
    int quote_state = 0;  // 0 = hors quote, 1 = single, 2 = double
    char quote_char;

    skip_whitespace(&ptr);
    while (*ptr)
    {
        if (quote_state == 0)
        {
            skip_whitespace(&ptr);
            if (*ptr == '\0') break;
        }

        token_start = ptr;
        if (quote_state)
        {
            // Dans quote, avancer jusqu'à quote fermante
            while (*ptr && *ptr != quote_char)
                ptr++;
            if (*ptr) // Fermante trouvée
            {
                // Ajoute le token incluant les quotes ? No, bash strip quotes, mais pour lex, on garde comme QUOTED
                add_new_token(&head, &current, token_start - 1, ptr - token_start + 2, TOKEN_QUOTED);  // +2 pour inclure quotes
                quote_state = 0;
                ptr++;  // Skip fermante
                continue;
            }
            else // Pas fermante
            {
                printf("Error: unclosed quote\n");
                free_token_list(head);
                return (NULL);
            }
        }
        type = char_type(ptr);
        if (type == CHAR_SINGLE_QUOTE || type == CHAR_DOUBLE_QUOTE)
        {
            quote_char = (type == CHAR_SINGLE_QUOTE ? '\'' : '"');
            quote_state = type;
            ptr++;  // Skip ouvrante
            token_start = ptr;  // Start après quote
            continue;  // Collectera le content dans la prochaine it
        }

        // Operators
        if (type == CHAR_PIPE)
        {
            add_new_token(&head, &current, ptr, 1, TOKEN_PIPE);
            ptr++;
            continue;
        }
        else if (is_heredoc(ptr))
        {
            add_new_token(&head, &current, ptr, 2, TOKEN_HEREDOC);
            ptr += 2;
            continue;
        }
        else if (is_append(ptr))
        {
            add_new_token(&head, &current, ptr, 2, TOKEN_APPEND);
            ptr += 2;
            continue;
        }
        else if (is_redir(*ptr))
        {
            add_new_token(&head, &current, ptr, 1, (*ptr == '<') ? TOKEN_REDIR_IN : TOKEN_REDIR_OUT);
            ptr++;
            continue;
        }

        // Word normal
        while (*ptr && !is_whitespace(*ptr) && !is_operator(*ptr) && !is_quote(*ptr))
            ptr++;
        add_new_token(&head, &current, token_start, ptr - token_start, TOKEN_WORD);
    }

    return (head);
}

void print_token(t_pre_token *token)
{
    printf("print_token called from: %p\n", __builtin_return_address(0));
    while (token)
    {
        printf("Token: %.*s (type: %s)\n", token->len, token->start, type_token[token->type]);  // Adapté à TOKEN_*
        token = token->next;
    }
}
