/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 04:06:56 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 20:26:46 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strings.h>
#include <ft_write.h>

static int	ft_base_is_valid(char *base)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(base);
	i = 0;
	j = 1;
	if (!base || len <= 1)
		return (1);
	while (base[i] && i < len)
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		while (base[j] && (base[i] != base[j]))
			j++;
		if (base[i] == base[j])
			return (1);
		i++;
		j = i + 1;
	}
	return (0);
}

static void	secure_write(int fd, char *c, size_t n)
{
	if (!write(fd, c, n))
		return ;
}

void	ft_putnbr_int(int n, int fd, size_t *fsize)
{
	unsigned int	un;
	char			c;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		un = (unsigned int)-n;
		(*fsize)++;
		secure_write(fd, "-", 1);
	}
	else
		un = n;
	if (un <= 9)
	{
		(*fsize)++;
		c = un + 48;
		secure_write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_int(un / 10, fd, fsize);
		ft_putnbr_int(un % 10, fd, fsize);
	}
}

void	ft_putnbr_base_ul(unsigned long nbr, char *base, int fd, size_t *fsize)
{
	unsigned long	unbr;

	if (ft_base_is_valid(base))
		return ;
	unbr = nbr;
	if (unbr < (unsigned long)ft_strlen(base))
	{
		(*fsize)++;
		ft_putchar_fd(base[unbr], fd);
	}
	else
	{
		ft_putnbr_base_ul(unbr / ft_strlen(base), base, fd, fsize);
		ft_putnbr_base_ul(unbr % ft_strlen(base), base, fd, fsize);
	}
}
