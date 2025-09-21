/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 05:06:03 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 18:40:41 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count_word(char *s, char c)
{
	int		cutnbr;
	size_t	i;

	i = 0;
	cutnbr = 0;
	while (s[i])
	{
		if ((cutnbr == 0 && s[i] != c) || (s[i] == c && s[i + 1] != c && s[i
					+ 1]))
			cutnbr++;
		i++;
	}
	return (cutnbr);
}

static void	ft_free_all(char **s, int alloc)
{
	size_t	i;

	i = 0;
	while (i < (size_t)alloc)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static char	*ft_strmaker(char **s, char c)
{
	char	*res;
	int		slen;
	int		i;

	slen = 0;
	while ((*s)[slen] != c && (*s)[slen] != '\0')
		slen++;
	res = malloc(sizeof(char) * (slen + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		res[i] = (*s)[i];
		i++;
	}
	res[i] = '\0';
	while ((*s)[i] == c)
		i++;
	(*s) += i;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		cutnbr;
	int		i;
	char	**res;

	if (!s)
		return (NULL);
	cutnbr = ft_count_word((char *)s, c);
	res = malloc(sizeof(char *) * (cutnbr + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s == c)
		s++;
	while (i < cutnbr)
	{
		res[i] = ft_strmaker((char **)&s, c);
		if (!res[i])
		{
			ft_free_all(res, i);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

// int	main(void)
// {
// 	char	*str;
// 	char	**strtab;
// 	char	c;
// 	int		i;

// 	str = "Monkeys are in the place,you pissed us and
// 		you will pay for it,
// 		fucking bastards!";
// 	c = 'a';
// 	i = 0;
// 	strtab = ft_split(str, c);
// 	while (strtab[i])
// 	{
// 		__builtin_printf("%s", strtab[i]);
// 		free(strtab[i]);
// 		i++;
// 	}
// 	free(strtab);
// 	return (0);
// }
