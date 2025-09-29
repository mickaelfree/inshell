/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 03:05:58 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 20:28:52 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_memory.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*res;

	total = nmemb * size;
	if (size != 0 && total / size != nmemb)
		return (malloc(0));
	res = malloc(total);
	if (!res)
		return (NULL);
	ft_memset(res, 0, total);
	return (res);
}
