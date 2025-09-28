/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:58:19 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 06:34:54 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>

char	*process_heredoc(char *delimiter)
{
	char	*line;
	char	template[40];
	int		fd;

	ft_memcpy(template, "/tmp/inshell_heredoc_XXXXXX", 27);
	template[27] = '\0';
	fd = mkstemp(template);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (ft_strdup(template));
}
