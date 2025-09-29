/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:23:26 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 20:18:26 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strings.h>

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int		i;
	unsigned int		len;

	len = 0;
	i = 0;
	while (dest[len] && len < size)
		len++;
	while (src[i] && (len + (i + 1) < size))
	{
		dest[len + i] = src[i];
		i++;
	}
	if (len + i < size)
		dest[len + i] = '\0';
	return (len + ft_strlen(src));
}
