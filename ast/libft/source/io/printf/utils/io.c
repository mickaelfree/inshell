/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:18 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/11 06:14:45 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "ft_printf/ft_printf.h"

ssize_t	_ft_printf_write_fd(t_printf_output *out, const char *buffer, \
		size_t size)
{
	ssize_t	ret;

	ret = write(out->fd, buffer, size);
	if (ret < 0)
	{
		out->error = PRINTF_OUTPUT_ERROR_IO;
		return (FAILURE);
	}
	else if (ret != (ssize_t) size)
	{
		out->error = PRINTF_OUTPUT_ERROR_SIZE;
		return (FAILURE);
	}
	return (ret);
}

ssize_t	_ft_printf_write_buffer(t_printf_output *out, const char *buffer, \
		size_t size)
{
	size_t	cursor;

	cursor = 0;
	while (cursor < size && out->cursor + 1 < out->size)
		out->buffer[out->cursor++] = buffer[cursor++];
	if (cursor != size)
	{
		out->error = PRINTF_OUTPUT_ERROR_SIZE;
		return (FAILURE);
	}
	return ((ssize_t) cursor);
}

ssize_t	ft_printf_write(t_printf_output *out, const char *buffer, size_t size)
{
	if (out->mode == PRINTF_OUTPUT_FD)
		return (_ft_printf_write_fd(out, buffer, size));
	else if (out->mode == PRINTF_OUTPUT_BUFFER)
		return (_ft_printf_write_buffer(out, buffer, size));
	out->error = PRINTF_OUTPUT_ERROR_IO;
	return (FAILURE);
}
