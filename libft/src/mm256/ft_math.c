/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:02:23 by dderny            #+#    #+#             */
/*   Updated: 2025/02/06 19:36:57 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm256.h"

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_sub(__m256i __a,
		__m256i __b)
{
	return ((__m256i)((__v8si)__a - (__v8si)__b));
}

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_add(__m256i __a,
		__m256i __b)
{
	return ((__m256i)((__v8si)__a + (__v8si)__b));
}

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_mullo(__m256i __a,
		__m256i __b)
{
	return ((__m256i)((__v8si)__a * (__v8si)__b));
}

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_div(__m256i __a,
		__m256i __b)
{
	return ((__m256i)((__v8si)__a / (__v8si)__b));
}
