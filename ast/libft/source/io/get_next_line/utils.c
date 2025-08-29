/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:26:05 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/02 19:32:21 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "get_next_line/get_next_line.h"
#include "libft.h"

char	*extract_line(t_buffer *buffer)
{
	char	*line;
	size_t	line_len;

	line_len = buffer->endl_cur - buffer->data + 1;
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	line[line_len] = '\0';
	ft_memcpy(line, buffer->data, line_len);
	ft_memcpy(buffer->data, buffer->data + line_len, buffer->len - line_len);
	buffer->len = buffer->len - line_len;
	return (line);
}

bool	fill_buffer(t_buffer *buffer, const int fd)
{
	ssize_t	read_len;
	size_t	last_search_pos;

	last_search_pos = 0;
	while (true)
	{
		buffer->endl_cur = strnchr((char *)(buffer->data + last_search_pos), \
				ENDL_CHAR, buffer->len - last_search_pos);
		if (buffer->endl_cur)
			return (true);
		if (expand_buffer(buffer))
			return (false);
		read_len = read(fd, (char *)(buffer->data + buffer->len), BUFFER_SIZE);
		if (read_len <= 0)
			break ;
		last_search_pos = buffer->len;
		buffer->len += read_len;
	}
	if (buffer->len > 0 && read_len == 0)
	{
		buffer->endl_cur = buffer->data + buffer->len - 1;
		return (true);
	}
	return (false);
}

t_buffer	*init_buffer(void)
{
	t_buffer	*buffer;

	buffer = malloc(sizeof(t_buffer));
	if (!buffer)
		return (NULL);
	if (BUFFER_SIZE > BASE_BUFFER_SIZE / 2)
		buffer->mem_size = BUFFER_SIZE * 2;
	else
		buffer->mem_size = BASE_BUFFER_SIZE;
	buffer->data = malloc(sizeof(char) * buffer->mem_size);
	if (!buffer->data)
	{
		free(buffer);
		return (NULL);
	}
	buffer->endl_cur = NULL;
	buffer->len = 0;
	return (buffer);
}

int	expand_buffer(t_buffer *buffer)
{
	while (buffer->mem_size < buffer->len + BUFFER_SIZE)
	{
		buffer->data = ft_realloc(buffer->data, \
				buffer->mem_size, \
				buffer->mem_size * 2);
		if (!buffer->data)
			return (1);
		buffer->mem_size *= 2;
	}
	return (0);
}

void	free_buffer(t_buffer **buffer_arr, int fd)
{
	if (buffer_arr[fd])
	{
		free(buffer_arr[fd]->data);
		free(buffer_arr[fd]);
		buffer_arr[fd] = NULL;
	}
}
