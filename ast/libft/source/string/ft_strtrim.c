/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:29 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:29 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"

static bool	ft_charset(const char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1);
	while (ft_charset(s1[start], set))
		start++;
	while (ft_charset(s1[end - 1], set) && end > start)
		end--;
	dst = malloc(sizeof(char) * (end - start + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (start < end)
		dst[i++] = s1[start++];
	dst[i] = '\0';
	return (dst);
}

static bool	ft_charset(const char c, char const *set)
{
	while (*set)
	{
		if (c == *set++)
			return (true);
	}
	return (false);
}
