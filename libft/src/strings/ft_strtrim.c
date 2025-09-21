/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:19:01 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 18:42:11 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_charset(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_check_charset(set, s1[start]))
		start++;
	while (end > start && ft_check_charset(set, s1[end - 1]))
		end--;
	result = malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (NULL);
	i = -1;
	while ((++i + start) < end)
		result[i] = s1[start + i];
	result[i] = '\0';
	return (result);
}
