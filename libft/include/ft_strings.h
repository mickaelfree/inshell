/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:36:15 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 19:43:19 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include <unistd.h>

/** @name FT_SPLIT**
** @brief Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
**
** @param s: The string to be split.
** @param c: The delimiter character.
** @return The array of new strings resulting from the split.
NULL if the allocation fails.
*/
char				**ft_split(char const *s, char c);

/** @name FT_STRCHR**
** @brief The strchr() function returns a pointer to the first occurrence of the
		character c in the string s.
**
** @param s: the destination string.
** @param c: the char to fill.
** @return a pointer to the first occurrence of the
		character c in the string s.
*/
char				*ft_strchr(const char *s, int c);

/** @name FT_STRDUP**
** @brief The  strdup()  function returns a pointer
 to a new string which is a duplicate
 of the string s. Memory for the new  string  is  obtained  with  mal‐
loc(3), and can be freed with free(3).
**
** @param src: the source string.
** @return a pointer to a new string which is a duplicate of the string s.
*/
char				*ft_strdup(char *src);

/** @name FT_STRITERI**
** @brief Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.
**
** @param s: The string on which to iterate.
** @param f: The function to apply to each character.
** @return none.
*/

char				*ft_strndup(char *src, size_t n);

/** @name FT_STRNDUP**
** @brief The strndup() function returns a pointer
 to a new string which is a duplicate
 of at most n characters from the string s. If s is longer than n,
	only n characters
 are copied,
	and a terminating null byte ('\0') is added.
        Memory for the new string
 is obtained with malloc(3), and can be freed with free(3).
**
** @param src: the source string.
** @param n: maximum number of characters to copy.
** @return a pointer to a new string which is a 
duplicate of at most n characters from s.
*/
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/** @name FT_STRJOIN**
** @brief Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
**
** @param s1: The prefix string.
** @param s2: The suffix string.
** @return The new string.
NULL if the allocation fails.
*/
char				*ft_strjoin(char const *s1, char const *s2);

/** @name FT_STRLCAT**
** @brief The strlcat() function appends the NUL-terminated string
src to the end of dst.
It will append at most size - ft_strlen(dst) - 1 bytes,
	NUL-terminating the result.
**
** @param dest: The destination string.
** @param src: The source string.
** @param size: The size.
** @return For strlcat() that means the initial length of dst plus
 the length of src.
While this may seem somewhat confusing, it was done to make truncation
detection simple.
Note,  however, that if strlcat() traverses size 
characters without finding
a NUL, the length of the string is considered to 
be size and  the  destina‐
tion  string  will  not be NUL-terminated (since 
there was no space for the
NUL).  This keeps strlcat() from running off the 
end of a string.  In prac‐
tice this should not happen (as it means that either
 size is  incorrect  or
that  dst  is not a proper “C” string).  The check
 exists to prevent poten‐
tial security problems in incorrect code.
*/
unsigned int		ft_strlcat(char *dest, char *src, unsigned int size);

/** @name FT_STRLCAT**
** @brief The strlcpy() function copies up to size - 1 characters from
 the NUL-terminated string src to dst, NUL-terminating the result.
**
** @param dest: The destination string.
** @param src: The source string.
** @param size: The size.
** @return The strlcpy() return the total
 length of the string tried to create. For strlcpy()
  that means the length of src.
*/
size_t				ft_strlcpy(char *dest, char *src, unsigned int size);

/** @name ft_strlen**
** @brief ft_strlen is supposed to calculate the length of a string.
**
** @param s: the string.
** @return The len of the string.
*/
size_t				ft_strlen(const char *s);

/** @name FT_STRLCAT**
** @brief Apply the function 'f' to each characters in the string 's'
 to create a new string (with malloc(3))
 resulting of the successive applications of 'f'.
**
** @param s: string over which to iterate
** @param f: function to apply to each character
** @return (a new string resulting of the successive applications of 'f');
 NULL if the memory allocations failed.
*/
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/** @name ft_strncmp**
** @brief The ft_strncmp() function lexicographically compare
the null-terminated strings s1 and s2.
**
** @param s1: The address pointed in a 1st string.
** @param s2: The address pointed in a 2nd string.
** @param n: number of char to compare.
** @return an integer greater than, equal to, or less than 0,
according as the string s1 is greater than, equal to,
	or less than the string s2.
*/
int					ft_strncmp(char *s1, char *s2, unsigned int n);

/** @name FT_STRNSTR**
** @brief The strnstr() function locates the first occurence of the
null-terminated string needle in the string haystack,
where not more than len characters are searched.
Characters that appear after a '\0' character are not searched.
**
** @param big: container research string;
** @param little: string to search.
** @return (If little is an empty string, big is returned);
 if little occurs nowhere in big,
 NULL is returned; otherwise a pointer to the first character
  of the first occurence of little is returned.
*/
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

/** @name FT_STRRCHR**
** @brief The strrchr() function is identical to
strchr(), except it locates the last occurence of c.
**
** @param s: container research string;
** @param c: the char to look for.
** @return The function strrchr() returns a pointer to the located
 character, or NULL if the character does not appear in the string.
*/
char				*ft_strrchr(const char *s, int c);

/** @name FT_STRTRIM**
** @brief Allocate (with malloc(3)) and returns a copy of s1,
 without the characters specified in set at the beginning and the end of s1.
**
** @param s1: string to trim.
** @param set: characters to trim.
** @return (ft_strtrim() returns a trimmed copy of s1);
 NULL if the memory allocation failed.
*/
char				*ft_strtrim(char const *s1, char const *set);

/** @name FT_SUBSTR**
** @brief Allocate (with malloc(3)) and return a new string from the string s.
 This new string starts at index 'start' and has a maximum size of 'len'.
**
** @param s: string from which to extract the new string.
** @param start: start index of the new string in the string 's'.
** @param len: maximum size of the new string.
** @return (ft_substr() returns the new string);
 NULL if the memory allocation failed.
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);

#endif