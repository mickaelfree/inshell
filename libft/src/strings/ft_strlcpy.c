/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:04:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/30 19:12:37 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size -1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

/*int	main(void)
{
	unsigned int		size = 0;
	char				src[36] = "Everyone as a part of monkey inside!";
	char				dest[36] = "";

	ft_strlcpy(dest, src, size);
	__builtin_printf("The source string is : %s\n", src);
	__builtin_printf("The dest string is : %s\n", dest);
	__builtin_printf("The size is egual too : %d", size);
}*/
