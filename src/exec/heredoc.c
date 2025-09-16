/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:58:19 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/06 21:31:27 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

char    *process_heredoc(char *delimiter)
{
    char    *line;

    char    template[] = "/tmp/inshell_heredoc_XXXXXX";
    int     fd;

    fd = mkstemp(template);
    if (fd == -1)
        return (NULL);
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    return (ft_strdup(template));
}
