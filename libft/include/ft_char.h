/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:16:18 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 19:17:34 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHAR_H
# define FT_CHAR_H

////CHAR/////////////////////////////////////////////////////////////////////

/** @name FT_ISALNUM **
** @brief checks for an alphanumeric character
**
** @param c: the character to test
** @return The values returned are nonzero if the character c
 falls into the tested class,
	and zero if not.
*/
int					ft_isalnum(int c);

/** @name FT_ISALPHA **
** @brief Check for an alphabetic character
**
** @param c: the character to test
** @return The values returned are nonzero if the character c 
falls into the tested class,
	and zero if not.
*/
int					ft_isalpha(int c);

/** @name FT_ISASCII**
** @brief checks whether c is a 7-bit unsigned char value that 
fits into the ASCII character set.
**
** @param c: the character to test
** @return The values returned are nonzero if the character c falls 
into the tested class,
	and zero if not.
*/
int					ft_isascii(int c);

/** @name FT_ISDIGIT**
** @brief checks for a digit (0 through 9).
**
** @param c: the character to test
** @return The values returned are nonzero if the character c falls
 into the tested class,
	and zero if not.
*/
int					ft_isdigit(int c);

/** @name FT_ISPRINT**
** @brief checks for any printable character including space.
**
** @param c: the character to test
** @return The values returned are nonzero if the character c falls
 into the tested class,
	and zero if not.
*/
int					ft_isprint(int c);

/** @name FT_TOLOWER**
** @brief convert uppercase letters to lowercase.
**
** @param c: the character to test
** @return The value returned is that of the converted letter,
	or c if the conversion was not possible.
*/
int					ft_tolower(int c);

/** @name FT_TOUPPER**
** @brief convert lowercase letters to uppercase.
**
** @param c: the character to test
** @return The value returned is that of the converted letter,
	or c if the conversion was not possible.
*/
int					ft_toupper(int c);

#endif