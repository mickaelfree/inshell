/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:23 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/02 19:11:48 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n && *((unsigned char *) s1) == *((unsigned char *) s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
		return (0);
	return (*((unsigned char *) s1) - *((unsigned char *) s2));
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size == 0)
		return (malloc(0));
	if (SIZE_MAX / size < nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

void	*ft_realloc(void *src, size_t old_size, size_t new_size)
{
	void	*dst;

	dst = (void *) malloc(sizeof(char) * new_size);
	if (!dst)
	{
		free(src);
		return (NULL);
	}
	if (new_size < old_size)
		old_size = new_size;
	ft_memcpy(dst, src, old_size);
	free(src);
	return (dst);
}
