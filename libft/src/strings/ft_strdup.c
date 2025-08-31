/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:15 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/30 19:12:37 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*strd;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	strd = malloc(i + 1);
	if (!strd)
		return (0);
	i = 0;
	while (*src)
	{
		strd[i] = *src++;
		i++;
	}
	strd[i] = 0;
	return (strd);
}
