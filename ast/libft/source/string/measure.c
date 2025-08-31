/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:31 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:31 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	size;

	size = 0;
	while (s[size] && maxlen--)
		size++;
	return (size);
}
