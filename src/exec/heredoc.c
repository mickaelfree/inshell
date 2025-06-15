/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:58:19 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/11 16:00:50 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"

int heredoc(char *limiter)
{

        while (1)
        {
                char *line = readline("heredoc> ");
                if (strcmp(line, limiter) == 0)
                {
                        free(line);
                        break;
                }
                write(STDOUT_FILENO, line, ft_strlen(line));
                write(STDOUT_FILENO, "\n", 1);
                free(line);
        }
        return (0);
}

