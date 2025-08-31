/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:37:11 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/31 04:46:13 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

static size_t	count_word(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static void	free_tab(char **tab, size_t w)
{
	size_t	i;

	i = 0;
	while (i < w)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**ft_tab(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

static char	**ft_tabword(char **tab, size_t w, const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	tab[w] = malloc(len + 1);
	if (!tab[w])
	{
		free_tab(tab, w);
		return (NULL);
	}
	ft_strlcpy(tab[w], s, len + 1);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	len;
	size_t	w;

	tab = ft_tab(s, c);
	if (!tab)
		return (NULL);
	w = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			tab = ft_tabword(tab, w++, s, c);
			if (!tab)
				return (NULL);
			s += len;
		}
		else
			s++;
	}
	tab[w] = NULL;
	return (tab);
}
