/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarunomane <sarunomane@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 03:14:00 by zsonie            #+#    #+#             */
/*   Updated: 2025/02/21 15:26:21 by sarunomane       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	core_system(char *buffer, char **line)
{
	size_t	bufsize;

	bufsize = BUFFER_SIZE;
	bufsize = gnl_buflen(buffer);
	*line = ft_strappend_to_line(*line, buffer, bufsize);
	if (gnl_strchr(buffer, '\n'))
	{
		gnl_strlcpy(buffer, gnl_strchr(buffer, '\n') + 1, BUFFER_SIZE + 1);
		return (1);
	}
	buffer[0] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[NBR_FD][BUFFER_SIZE + 1];
	char		*line;
	int			readcheck;

	if (fd < 0 || fd >= NBR_FD)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (!buffer[fd][0])
		{
			readcheck = read(fd, buffer[fd], BUFFER_SIZE);
			if (readcheck < 0)
			{
				free(line);
				buffer[fd][0] = '\0';
				return (NULL);
			}
			buffer[fd][readcheck] = 0;
			if (readcheck == 0)
				return (line);
		}
		if (core_system(buffer[fd], &line))
			return (line);
	}
}
