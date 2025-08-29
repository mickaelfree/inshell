/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:25 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:25 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	offset;

	i = 0;
	while (dst[i] && i < size)
		i++;
	offset = i;
	while (src[i - offset] && i + 1 < size)
	{
		dst[i] = src[i - offset];
		i++;
	}
	if (offset < size)
		dst[i] = '\0';
	return (offset + ft_strlen(src));
}
