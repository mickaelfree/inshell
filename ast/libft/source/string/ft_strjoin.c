/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:28 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:28 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s1, s1_len);
	ft_memcpy(dst + s1_len, s2, s2_len);
	dst[s1_len + s2_len] = '\0';
	return (dst);
}
