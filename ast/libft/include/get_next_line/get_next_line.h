/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:26:00 by jureix-c          #+#    #+#             */
/*   Updated: 2025/05/05 22:27:49 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// INCLUDES
# include <stdlib.h>
# include <stdbool.h>

// DEFINES
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define BASE_BUFFER_SIZE 2048

# define ENDL_CHAR '\n'

// STRUCTURES
typedef struct s_buffer
{
	char	*data;
	char	*endl_cur;
	size_t	len;
	size_t	mem_size;
}	t_buffer;

// PROTOTYPES
// Get next line
char		*get_next_line(int fd);
void		get_next_line_cleanup(void);

// Utils
char		*extract_line(t_buffer *buffer);
bool		fill_buffer(t_buffer *buffer, const int fd);
t_buffer	*init_buffer(void);
int			expand_buffer(t_buffer *buffer);
void		free_buffer(t_buffer **buffer_arr, int fd);

#endif
