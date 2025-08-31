/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:36:51 by jureix-c          #+#    #+#             */
/*   Updated: 2025/05/06 00:30:43 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHFT_H
# define MATHFT_H

// FUNCTIONS
static inline int	int_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static inline int	int_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static inline int	int_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

#endif
