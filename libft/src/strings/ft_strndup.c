/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:34:48 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 20:19:41 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(char *src, size_t n)
{
	char	*strd;
	size_t	i;
	size_t	src_len;

	i = 0;
	if (!src)
		return (NULL);
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (n > src_len)
		n = src_len;
	strd = malloc(n + 1);
	if (!strd)
		return (NULL);
	while (i < n && src[i])
	{
		strd[i] = src[i];
		i++;
	}
	strd[i] = '\0';
	return (strd);
}
