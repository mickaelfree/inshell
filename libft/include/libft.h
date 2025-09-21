/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:32:53 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 18:48:33 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

////////////////////////////////INCLUDES//////////////////////////////////////

# include "get_next_line.h"
# include "time_manager.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

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
////////////////////////////////////////////////////

/** @name FT_ISALPHA **
** @brief Check for an alphabetic character
**
** @param c: the character to test
** @return The values returned are nonzero if the character c 
falls into the tested class,
	and zero if not.
*/
int					ft_isalpha(int c);
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

/** @name FT_ISDIGIT**
** @brief checks for a digit (0 through 9).
**
** @param c: the character to test
** @return The values returned are nonzero if the character c falls
 into the tested class,
	and zero if not.
*/
int					ft_isdigit(int c);
////////////////////////////////////////////////////////////

/** @name FT_ISPRINT**
** @brief checks for any printable character including space.
**
** @param c: the character to test
** @return The values returned are nonzero if the character c falls
 into the tested class,
	and zero if not.
*/
int					ft_isprint(int c);
////////////////////////////////////////////////////////////

/** @name FT_TOLOWER**
** @brief convert uppercase letters to lowercase.
**
** @param c: the character to test
** @return The value returned is that of the converted letter,
	or c if the conversion was not possible.
*/
int					ft_tolower(int c);
////////////////////////////////////////////////////////////

/** @name FT_TOUPPER**
** @brief convert lowercase letters to uppercase.
**
** @param c: the character to test
** @return The value returned is that of the converted letter,
	or c if the conversion was not possible.
*/
int					ft_toupper(int c);
////////////////////////////////////////////////////////////

///////////////////////////////
////CONVERT////////////////////////////
////////////////////////////////////////////////////////////

/** @name FT_ATOF**
** @brief convert ascii to float (double).
**
** @param str: the string to convert.
** @return The converted double or 0 on error.
*/
double				ft_atof(const char *str);
////////////////////////////////////////////////////////////

/** @name FT_ATOI**
** @brief convert ascii to int
**
** @param str: the string to convert.
** @return The converted int or 0 on error.
*/
int					ft_atoi(const char *str);
////////////////////////////////////////////////////////////

/** @name FT_ITOA**
** @brief convert int to ascii.
**
** @param n: the int to convert.
** @return The converted strings.
*/
char				*ft_itoa(int n);
////////////////////////////////////////////////////////////

////LIST////////////////////////////////////////////////////

/** @name SINGLYCHAINEDLIST**
** @brief a simple chained list struct.
* @param content: current node
* @param next: next node
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
////////////////////////////////////////////////////////////

/** @name FT_LSTADD_BACK**
** @brief add a node from the back of the list.
**
** @param lst: the parent list.
** @param new: the node to add.
** @return nothing.
*/
void				ft_lstadd_back(t_list **lst, t_list *new);
////////////////////////////////////////////////////////////

/** @name FT_LSTADD_FRONT**
** @brief add a node to the front of the list.
**
** @param lst: the parent list.
** @param new: the node to add.
** @return nothing.
*/
void				ft_lstadd_front(t_list **lst, t_list *new);
////////////////////////////////////////////////////////////

/** @name FT_LSTCLEAR**
** @brief clear and free all node of a chained list.
**
** @param lst: the list.
** @param del: the function to del.
** @return nothing.
*/
void				ft_lstclear(t_list **lst, void (*del)(void *));
////////////////////////////////////////////////////////////

/** @name FT_LSTDELONE**
** @brief clear and free a node.
**
** @param lst: the list.
** @param del: the function to del.
** @return nothing.
*/
void				ft_lstdelone(t_list *lst, void (*del)(void *));
////////////////////////////////////////////////////////////

/** @name FT_LSTITER**
** @brief Iterates the list ’lst’ and applies the function ’f’
on the content of each node.
**
** @param lst: the address of a pointer to a node.
** @param f: The address of the function used to iterate on the list.
** @return nothing.
*/
void				ft_lstiter(t_list *lst, void (*f)(void *));
////////////////////////////////////////////////////////////

/** @name FT_LSTLAST**
** @brief Returns the last node of the list.
**
** @param lst: The beginning of the list.
** @return The length of the list
*/
t_list				*ft_lstlast(t_list *lst);
////////////////////////////////////////////////////////////

/** @name FT_LSTSIZE**
** @brief Counts the number of nodes in a list.
**
** @param lst: The beginning of the list.
** @return The length of the list
*/
int					ft_lstsize(t_list *lst);
////////////////////////////////////////////////////////////

/** @name FT_LSTMAP**
** @brief Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.
**
** @param lst: The beginning of the list.
** @param f: The address of the function used to iterate on the list.
** @param del: The address of the function used to delete
the content of a node if needed.
** @return The new list. NULL if the allocation fails.
*/
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
////////////////////////////////////////////////////////////

/** FT_LSTNEW**
** @brief Allocates (with malloc(3)) and returns a new node.
**
** @param content: content of the new node.
** @return the created chained node.
*/
t_list				*ft_lstnew(void *content);
////////////////////////////////////////////////////////////

////MEMORY/////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

////STRINGS///////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

/** @name ft_strlen**
** @brief ft_strlen is supposed to calculate the length of a string.
**
** @param s: the string.
** @return The len of the string.
*/
size_t				ft_strlen(const char *s);
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////

////WRITE///////////////////////////////////////////////////

/** @name FT_PUTCHAR_FD**
** @brief The ft_putchar_fd() function writes the
character c on the file descriptor fd.
**
** @param c: character to write.
** @param fd: file descriptor on which to write.
** @return none.
*/
void				ft_putchar_fd(char c, int fd);
////////////////////////////////////////////////////////////

/** @name FT_PUTENDL_FD**
** @brief write the string s, followed by a newline,
on the file descriptor fd.
**
** @param s: string to display.
** @param fd: file descriptor on which to write.
** @return none.
*/
void				ft_putendl_fd(char *s, int fd);
////////////////////////////////////////////////////////////

/** @name FT_PUTNBR_FD**
** @brief write the int n on the file descriptor fd.
**
** @param n: int to write.
** @param fd: file descriptor on which to write.
** @return none.
*/
void				ft_putnbr_fd(int n, int fd);
////////////////////////////////////////////////////////////

/** @name FT_PUTSTR_FD**
** @brief Write a function that displays a string on the standard output.
**
** @param s: string to display.
** @param fd: file descriptor on which to write.
** @return none.
*/
void				ft_putstr_fd(char *s, int fd);
////////////////////////////////////////////////////////////

#endif
