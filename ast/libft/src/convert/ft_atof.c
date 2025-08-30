/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:29 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/30 19:07:31 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <math.h>

double	ft_atof(const char *str)
{
	int		i;
	double	num;
	int		precision_factor;
	const char	*precision_part;

	i = -1;
	num = 0;
	precision_factor = 0;
	precision_part = str;
	num = ft_atoi(str);
	while (str[++i] && ft_isdigit(str[i]))
		precision_part++;
	if (*precision_part == '.' || *precision_part == ',')
		precision_part++;
	i = -1;
	while (precision_part[++i] && ft_isdigit(precision_part[i]))
		precision_factor++;
	precision_factor = pow(10, precision_factor);
	num = num + (double)ft_atoi(precision_part)/(double)precision_factor;
	return (num);
}

// int main(int ac, char **av)
// {
// 	printf("%.5f\n", atof(av[1]));
// 	printf("%.5f\n", ft_atof(av[1]));
// 	return (1);
// }
