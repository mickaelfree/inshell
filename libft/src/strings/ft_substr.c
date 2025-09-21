/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:20:05 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 18:42:23 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sub = malloc(1);
		if (!sub)
			return (0);
		sub[0] = '\0';
		return (sub);
	}
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	sub = malloc(len + 1);
	if (!sub)
		return (0);
	i = 0;
	while (i++ < len)
		sub[i - 1] = s[start + i - 1];
	sub[len] = '\0';
	return (sub);
}
