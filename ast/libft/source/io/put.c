/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:21 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:21 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	lu_n;

	if (n < 0)
	{
		lu_n = -((unsigned int) n);
		ft_putchar_fd('-', fd);
	}
	else
		lu_n = n;
	if (lu_n > 9)
		ft_putnbr_fd(lu_n / 10, fd);
	ft_putchar_fd(lu_n % 10 + '0', fd);
}
