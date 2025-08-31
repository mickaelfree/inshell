/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:31 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/02 19:17:11 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char) *s++ == (unsigned char) c)
			return ((char *) s - 1);
	}
	if (!(unsigned char) c)
		return ((char *) s);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	const char	*begin;

	begin = s;
	while (*s)
		s++;
	while (s >= begin)
	{
		if ((unsigned char) *s-- == (unsigned char) c)
			return ((char *) s + 1);
	}
	return (NULL);
}

char	*strnchr(char *str, char c, size_t maxlen)
{
	while (maxlen-- && *str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *) big);
	i = 0;
	while (big[i] && i < len)
	{
		j = i;
		while (little[j - i] && big[j] == little[j - i] && j < len)
			j++;
		if (!little[j - i])
			return ((char *) big + i);
		i++;
	}
	return (NULL);
}
