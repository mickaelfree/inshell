/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarunomane <sarunomane@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:02:23 by dderny            #+#    #+#             */
/*   Updated: 2025/02/16 06:28:18 by sarunomane       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm256.h"

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_slli(__m256i __a, int __n)
{
	return ((__m256i)((__v8si)__a << __n));
}

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_srli(__m256i __a, int __n)
{
	return ((__m256i)((__v8si)__a >> __n));
}

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_and(__m256i __a,
		__m256i __b)
{
	return (__a & __b);
}

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_or(__m256i __a,
		__m256i __b)
{
	return (__a | __b);
}

__m256i	/* __attribute__((__always_inline__))	*/ft_mm256_set1(int __i)
{
	return ((__m256i)(__v8si){__i, __i, __i, __i, __i, __i, __i, __i});
}
