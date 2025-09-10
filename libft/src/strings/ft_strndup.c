/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:34:48 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/10 19:37:00 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
