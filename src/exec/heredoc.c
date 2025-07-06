/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:58:19 by mickmart          #+#    #+#             */
/*   Updated: 2025/07/06 18:00:25 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"

char *process_heredoc(char *delimiter)
{
    char *line;
    char *temp_file = "/tmp/inshell_heredoc_XXXXXX";
    int fd;
    
    // Créer un fichier temporaire
    fd = mkstemp(temp_file);
    if (fd == -1)
        return NULL;
    
    // Lire les lignes jusqu'au délimiteur
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        
        // Vérifier si c'est le délimiteur
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        
        // Écrire la ligne dans le fichier temporaire
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    
    close(fd);
    return ft_strdup(temp_file);
}
