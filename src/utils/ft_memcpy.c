/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:45:44 by mickmart          #+#    #+#             */
/*   Updated: 2024/11/06 09:45:46 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if ((!src && !dest) || dest == src || n <= 0)
		return (dest);
	if (n <= 0)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}
