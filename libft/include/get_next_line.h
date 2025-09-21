/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarunomane <sarunomane@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:09:50 by zsonie            #+#    #+#             */
/*   Updated: 2025/02/21 15:23:47 by sarunomane       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

////////////////////////////////////////////////////
///////////////////////////////////////////////////

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef NBR_FD
#  define NBR_FD 1024
# endif

# if BUFFER_SIZE <= 0
#  error BUFFER_SIZE cannot be <= 0 
# endif

# if NBR_FD <= 0
#  error NBR_FD cannot be <= 0 
# endif

/////////////////////////////////////////////////////
//----------------------------------INCLUDE---------------------------------//
///////////////////////////////////////////////////

# include <unistd.h>
# include <stdlib.h>

/////////////////////////////////////////////////////
//---------------------------------FUNCTION---------------------------------//
///////////////////////////////////////////////////

size_t	gnl_ft_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
size_t	gnl_buflen(char *buffer);
size_t	gnl_strlcpy(char *dest, char *src, size_t size);
char	*ft_strappend_to_line(char *s1, char *s2, size_t bufsize);
char	*get_next_line(int fd);

#endif