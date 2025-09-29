/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:16:18 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 19:18:33 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONVERT_H
# define FT_CONVERT_H

/** @name FT_ATOF**
** @brief convert ascii to float (double).
**
** @param str: the string to convert.
** @return The converted double or 0 on error.
*/
double				ft_atof(const char *str);

/** @name FT_ATOI**
** @brief convert ascii to int
**
** @param str: the string to convert.
** @return The converted int or 0 on error.
*/
int					ft_atoi(const char *str);

/** @name FT_ITOA**
** @brief convert int to ascii.
**
** @param n: the int to convert.
** @return The converted strings.
*/
char				*ft_itoa(int n);

#endif