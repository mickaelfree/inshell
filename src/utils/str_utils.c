/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:22:34 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/27 16:39:17 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

size_t	ft_strlen(const char *str)
{
	const char	*start;

	if (!str)
		return (0);
	start = str;
	while (1)
	{
		if (!str[0])
			return (str - start);
		if (!str[1])
			return (str - start + 1);
		if (!str[2])
			return (str - start + 2);
		if (!str[3])
			return (str - start + 3);
		str += 4;
	}
}
size_t	ft_strlcpy(char *dst, const char *src, size_t sz)
{
	const char	*s;
	size_t		len;

	s = src;
	while (*s)
		s++;
	len = s - src;
	if (!sz || !dst || !src)
		return (len);
	s = src;
	while (--sz && *s)
		*dst++ = *s++;
	*dst = '\0';
	return (len);
}
char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

static char	*ft_strsearch(const char *big, const char *little, size_t len)
{
	const char	*start_big;
	const char	*start_little;
	size_t		r_len;

	while (*big && len)
	{
		start_big = big;
		start_little = little;
		r_len = len;
		while (*start_big && *start_little && *start_big == *start_little
			&& r_len--)
		{
			start_big++;
			start_little++;
		}
		if (!*start_little)
			return ((char *)big);
		len--;
		big++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (*big == '\0' && !*little)
		return ((char *)big);
	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	if (len < little_len)
		return (NULL);
	return (ft_strsearch(big, little, len));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	char	*start;
	size_t	lentotal;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lentotal = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(sizeof(char) * lentotal);
	if (!dest)
		return (NULL);
	start = dest;
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
	return (start);
}
