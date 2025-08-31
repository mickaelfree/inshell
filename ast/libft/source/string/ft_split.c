/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:26 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:26 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

static int			ft_split_count(char const *s, char c);
static size_t		ft_split_strlen(char const *s, char c);
static char			**ft_split_free(char **arr, int current_idx);
static const char	*ft_split_strcpy(char *dst, const char *src, char c);

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		arr_idx;

	arr = malloc(sizeof(char *) * (ft_split_count(s, c) + 1));
	if (!arr)
		return (NULL);
	arr_idx = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		arr[arr_idx] = malloc(sizeof(char) * (ft_split_strlen(s, c) + 1));
		if (!arr[arr_idx])
			return (ft_split_free(arr, arr_idx));
		s = ft_split_strcpy(arr[arr_idx++], s, c);
	}
	arr[arr_idx] = NULL;
	return (arr);
}

static int	ft_split_count(char const *s, char c)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	while (*s)
	{
		if (*s++ == c)
			in_word = false;
		else if (!in_word)
		{
			in_word = true;
			count++;
		}
	}
	return (count);
}

static size_t	ft_split_strlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	**ft_split_free(char **arr, int current_idx)
{
	while (current_idx >= 0)
		free(arr[current_idx--]);
	free(arr);
	return (NULL);
}

static const char	*ft_split_strcpy(char *dst, const char *src, char c)
{
	while (*src && *src != c)
		*dst++ = *src++;
	*dst = '\0';
	return (src);
}
