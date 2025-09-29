/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:16:18 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 19:43:28 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
# define FT_MEMORY_H

# include <unistd.h>

/** @name FT_BZERO**
** @brief The  bzero() function erases the data in the n 
bytes of the memory starting
at the location pointed to by s, by writing zeros (bytes  
containing  '\0')
to that area.
**
** @param s: pointed location.
** @param n: number of bytes to write.
** @return the created chained node.
*/
void				*ft_bzero(void *s, size_t n);

/** @name FT_CALLOC**
** @brief The calloc() function allocates memory for an
 array of  nmemb  elements  of
		size  bytes each and returns a pointer to
               the allocated memory.  The memory
		is set to zero.  If nmemb or size is 0,
				then  calloc()  returns  a  
                            unique
		pointer value that can later be successfully 
              passed to free().
**
** @param nmemb: number of elements.
** @param size: number of bytes of each elements.
** @return a pointer to the allocated memory.
*/
void				*ft_calloc(size_t nmemb, size_t size);

/** @name FT_MEMCHR**
** @brief The  memchr() function scans the initial n bytes
 of the memory area pointed
		to by s for the first instance of c.  Both c
               and the bytes  of  the  memory
		area pointed to by s are interpreted as
               unsigned char.
**
** @param s: the start of the memory area pointed.
** @param c: the charset to scan for.
** @param n: number of bytes to scans.
** @return the new address if the charset has been scanned,
 0 if not scanned.
*/
void				*ft_memchr(const void *s, int c, size_t n);

/** @name FT_MEMCMP**
** @brief The  memcmp()  function compares the first n
 bytes (each interpreted as un‐
		signed char) of the memory areas s1 and s2.
**
** @param s1: a string to compare.
** @param s2: a string to compare.
** @param n: number of bytes.
** @return different to 0 if not identical or 0 if identical.
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/** @name FT_MEMCPY**
** @brief The  memcpy()  function  copies n bytes from 
memory area src to memory area
		dest.  The memory areas must not overlap. 
               Use memmove(3) if the memory ar‐
		eas do overlap.
**
** @param dest: the destination string.
** @param src: the string to copy.
** @param n: number of bytes.
** @return dest.
*/
void				*ft_memcpy(void *dest, const void *src, size_t n);

/** @name FT_MEMMOVE**
** @brief The  memmove()  function copies n bytes from 
memory area src to memory area
		dest.  The memory areas may overlap: copying
                takes  place  as  though  the
		bytes  in src are first copied into a temporary
               array that does not overlap
		src or dest,
			and the bytes are then copied  from  the
                      temporary  array  to
		dest.
**
** @param dest: the destination string.
** @param src: the string to move threw a tmp array.
** @param n: number of bytes.
** @return dest.
*/
void				*ft_memmove(void *dest, const void *src, size_t n);

/** @name FT_MEMSET**
** @brief The memset() function fills the first n bytes of
 the memory area pointed to
		by s with the constant byte c.
**
** @param s: the destination string.
** @param c: the char to fill.
** @param n: number of bytes.
** @return s.
*/
void				*ft_memset(void *s, int c, size_t n);

#endif