/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm256.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:12:45 by dderny            #+#    #+#             */
/*   Updated: 2025/09/29 20:36:52 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM256_H
# define MM256_H

#include <immintrin.h>

/**
** @brief Perform a left logical shift on a 256-bit integer vector.
**
** @param __a: The 256-bit integer vector to be shifted.
** @param __n: The number of bits to shift.
** @return The result of the left logical shift.
*/
extern __m256i	ft_mm256_slli(__m256i __a, int __n);
// __attribute__((__always_inline__));

/**
** @brief Perform a right logical shift on a 256-bit integer vector.
**
** @param __a: The 256-bit integer vector to be shifted.
** @param __n: The number of bits to shift.
** @return The result of the right logical shift.
*/
extern __m256i	ft_mm256_srli(__m256i __a, int __n);
// __attribute__((__always_inline__));

/**
** @brief Divide two 256-bit integer vectors.
**
** @param __a: The dividend 256-bit integer vector.
** @param __b: The divisor 256-bit integer vector.
** @return The result of the division.
*/
extern __m256i	ft_mm256_div(__m256i __a, __m256i __b);
// __attribute__((__always_inline__));

/**
** @brief Multiply two 256-bit integer vectors.
**
** @param __a: The first 256-bit integer vector.
** @param __b: The second 256-bit integer vector.
** @return The result of the multiplication.
*/
extern __m256i	ft_mm256_mullo(__m256i __a, __m256i __b);
// __attribute__((__always_inline__));

/**
** @brief Add two 256-bit integer vectors.
**
** @param __a: The first 256-bit integer vector.
** @param __b: The second 256-bit integer vector.
** @return The result of the addition.
*/
extern __m256i	ft_mm256_add(__m256i __a, __m256i __b);
// __attribute__((__always_inline__));

/**
** @brief Subtract one 256-bit integer vector from another.
**
** @param __a: The 256-bit integer vector to be subtracted from.
** @param __b: The 256-bit integer vector to subtract.
** @return The result of the subtraction.
*/
extern __m256i	ft_mm256_sub(__m256i __a, __m256i __b);
// __attribute__((__always_inline__));

/**
** @brief Perform a bitwise AND operation on two 256-bit integer vectors.
**
** @param __a: The first 256-bit integer vector.
** @param __b: The second 256-bit integer vector.
** @return The result of the bitwise AND operation.
*/
extern __m256i	ft_mm256_and(__m256i __a, __m256i __b);
// __attribute__((__always_inline__));

/**
** @brief Perform a bitwise OR operation on two 256-bit integer vectors.
**
** @param __a: The first 256-bit integer vector.
** @param __b: The second 256-bit integer vector.
** @return The result of the bitwise OR operation.
*/
extern __m256i	ft_mm256_or(__m256i __a, __m256i __b);
// __attribute__((__always_inline__));

/**
** @brief Set all elements of a 256-bit integer vector to a specified value.
**
** @param __i: The value to set.
** @return The 256-bit integer vector with all elements set to
**	the specified value.
*/
extern __m256i	ft_mm256_set1(int __i);

#endif