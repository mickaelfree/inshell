/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:30 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:30 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static size_t	ft_min(size_t a, size_t b);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	st_start;
	size_t	src_len;
	size_t	i;

	st_start = (size_t) start;
	src_len = ft_strlen(s);
	if (st_start >= src_len)
		st_start = src_len;
	dst = malloc(sizeof(char) * (ft_min(src_len - st_start, len) + 1));
	if (!dst)
		return (NULL);
	s += st_start;
	i = 0;
	while (s[i] && len--)
	{
		dst[i] = s[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
