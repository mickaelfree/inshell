/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:25:54 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/02 19:37:31 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <sys/select.h>

#include "get_next_line/get_next_line.h"

char	*read_line(t_buffer *buffer, const int fd)
{
	if (fill_buffer(buffer, fd))
		return (extract_line(buffer));
	return (NULL);
}

void	clean_buffer_array(t_buffer **buffer_arr)
{
	int	i;

	i = 0;
	while (i < FD_SETSIZE)
		free_buffer(buffer_arr, i++);
}

char	*_get_next_line(int fd, bool cleanup)
{
	static t_buffer	*buffer[FD_SETSIZE] = {NULL};
	char			*line;

	if (cleanup)
	{
		clean_buffer_array(buffer);
		return (NULL);
	}
	if (fd < 0 || fd >= FD_SETSIZE)
		return (NULL);
	if (!buffer[fd])
	{
		if (BUFFER_SIZE <= 0 || BASE_BUFFER_SIZE <= 0)
			return (NULL);
		buffer[fd] = init_buffer();
		if (!buffer[fd])
			return (NULL);
	}
	line = read_line(buffer[fd], fd);
	if (!line)
		free_buffer(buffer, fd);
	return (line);
}

char	*get_next_line(int fd)
{
	return (_get_next_line(fd, false));
}

void	get_next_line_cleanup(void)
{
	_get_next_line(0, true);
}
