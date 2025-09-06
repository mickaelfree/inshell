/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 05:34:47 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/06 20:28:49 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Get the length of a string
size_t	gnl_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// Get everything after the charset
char	*gnl_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (&((char *)s)[i]);
	return (0);
}

// Copy the string from src to dest
size_t	gnl_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (gnl_ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (gnl_ft_strlen(dest));
}

size_t	gnl_buflen(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i);
}

// Join 2 differents strings to one
char	*ft_strappend_to_line(char *s1, char *s2, size_t bufsize)
{
	char	*result;
	ssize_t	s1len;
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = -1;
	if (!s2)
		return (NULL);
	s1len = 0;
	if (s1)
		s1len = gnl_ft_strlen(s1);
	result = malloc(sizeof(char) * (s1len + bufsize + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	while (++i < s1len)
		result[i] = s1[i];
	while (++j < (ssize_t)bufsize)
		result[(i + j)] = s2[j];
	result[s1len + bufsize] = '\0';
	free(s1);
	return (result);
}
