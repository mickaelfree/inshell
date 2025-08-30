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

static char	*type_token[] = {"WORD", "QUOTED", "PIPE", "REDIR_IN", "REDIR_OUT",
		"HEREDOC", "APPEND"};


// Avance p jusqu’à la fin du mot "non quoté" (arrêt: espace, opérateur, quote, fin)
static const char *scan_bare_word(const char *p)
{
    while (*p && !is_whitespace(*p) && !is_operator(*p) && !is_quote(*p))
        p++;
    return p;
}
void add_token(t_pre_token **head, char *start, int len, int type, t_quote quote)
 {
     t_pre_token *n = malloc(sizeof(*n));
     if (!n) return;
     n->start = start;
     n->len   = len;
     n->type  = type;
+    n->quote_state = quote;
     n->next  = NULL;
 
     if (!*head) { *head = n; return; }
     t_pre_token *t = *head;
     while (t->next) t = t->next;
     t->next = n;
 }

// Scanne un bloc quoté. Retourne:
//  - end: juste APRÈS la quote fermante si trouvée
//  - *inner_start = début "à l’intérieur" (après la quote ouvrante)
//  - *inner_len   = longueur interne (sans quotes)
//  - *qtype       = QUOTE_SINGLE / QUOTE_DOUBLE
//  - si quote non fermée: retourne NULL
static const char *scan_quoted(const char *p, const char **inner_start, int *inner_len, t_quote *qtype)
{
    char qc = *p; // ' ou "
    *qtype = (qc == '\'') ? QUOTE_SINGLE : QUOTE_DOUBLE;
    p++; // saute la quote ouvrante
    const char *s = p;
    if (qc == '\'') {
        // single quotes: littéral jusqu'à la prochaine '
        while (*p && *p != '\'')
            p++;
        if (*p != '\'')
            return NULL; // non fermé
        *inner_start = s;
        *inner_len   = (int)(p - s);
        return p + 1; // saute la quote fermante
    } else {
        // double quotes: autoriser \" pour échapper une double-quote
        while (*p) {
            if (*p == '\\' && *(p+1) == '"') {
                p += 2;   // garder \" dans la valeur ? -> on garde brut ici, on ne retire pas le '\'
                continue;
            }
            if (*p == '"')
                break;
            p++;
        }
        if (*p != '"')
            return NULL; // non fermé
        *inner_start = s;
        *inner_len   = (int)(p - s);
        return p + 1;
    }
}

// Gestion d'erreur quote non fermée — adapte à ta gestion d'erreurs
static void report_unclosed_quote(char q)
{
    fprintf(stderr, "inshell: unexpected EOF while looking for matching `%c'\n", q);
    fprintf(stderr, "inshell: syntax error: unexpected end of file\n");
     g_last_exit_status = 2; // si tu as ce global
}

t_pre_token *tokenize_line(const char *line)
 {
     t_pre_token *head = NULL;
     const char *p = line;
 
     while (*p) {
         if (is_whitespace(*p)) { p++; continue; }
 
         if (is_operator(*p)) {
            int len_op = 1;
            if ((p[0] == '<' || p[0] == '>') && p[1] == p[0])
                len_op = 2;
            add_token(&head, (char*)p, len_op, TOKEN_OPERATOR, QUOTE_NONE);
            p += len_op;
             continue;
         }
 
         if (is_quote(*p)) {
            const char *inner;
            int         ilen;
            t_quote     qtype;
            const char *end = scan_quoted(p, &inner, &ilen, &qtype);
            if (!end) {
                report_unclosed_quote(*p);
                // libère les tokens déjà alloués si nécessaire
                // return NULL; ou bien marque une erreur dans le parser
                return head; // si tu veux laisser le haut niveau détecter l'erreur
            }
            // IMPORTANT: on ajoute un TOKEN_WORD dont start/len sont "sans quotes"
            add_token(&head, (char*)inner, ilen, TOKEN_WORD, qtype);
            p = end;
            continue;
        }

        // WORD non-quoté
        const char *s = p;
        p = scan_bare_word(p);
        add_token(&head, (char*)s, (int)(p - s), TOKEN_WORD, QUOTE_NONE);
     }
     return head;
 }

