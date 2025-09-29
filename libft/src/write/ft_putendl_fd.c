/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:06:53 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 20:35:09 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_write.h>
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int		i;

	if (!s || fd <= 0)
		return ;
	i = 0;
	while (s[i])
	{
		if (write (fd, &s[i], 1) < 0)
			return ;
		i++;
	}
	ft_putchar_fd('\n', fd);
}
