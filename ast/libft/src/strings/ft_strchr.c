/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarunomane <sarunomane@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:28:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/02/14 21:29:20 by sarunomane       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);	
	while (s[i] && s[i] != (char ) c)
	{
		i++;
	}
	if (s[i] == (char ) c)
		return (&((char *)s)[i]);
	return (0);
}
