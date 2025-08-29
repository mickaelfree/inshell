/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:32 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/11 05:36:00 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// INCLUDES
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>

# include "libft.h"
# include "nodes.h"

// DEFINES
# define FT_PRINTF_FLAGS "-0+ #hlLjzt"
# define FT_PRINTF_MODIFIERS "cspdiuxXn%"

# define MALLOC_ERROR -2

// STRUCTURES
typedef enum s_printf_output_mode
{
	PRINTF_OUTPUT_FD,
	PRINTF_OUTPUT_BUFFER
}	t_printf_output_mode;

typedef enum s_printf_output_error
{
	PRINTF_OUTPUT_ERROR_NONE,
	PRINTF_OUTPUT_ERROR_SIZE,
	PRINTF_OUTPUT_ERROR_IO,
}	t_printf_output_error;

typedef struct s_printf_output
{
	t_printf_output_mode	mode;
	t_printf_output_error	error;
	// File descriptor mode
	int						fd;
	// Buffer mode
	char					*buffer;
	size_t					size;
	size_t					cursor;
}	t_printf_output;

typedef struct s_printf_data
{
	// Parameters
	const char			*format;
	t_printf_output		output;
	// Logic
	t_printf_node		*nodes;
}	t_printf_data;

// PROTOTYPES
int		ft_printf(const char *format, ...);
int		ft_vprintf(const char *format, va_list argv);
// File descriptor prototypes
int		ft_dprintf(int fd, const char *format, ...);
int		ft_vdprintf(int fd, const char *format, va_list argv);
// Buffer prototypes
int		ft_sprintf(char *str, const char *format, ...);
int		ft_snprintf(char *str, size_t size, const char *format, ...);
int		ft_vsprintf(char *str, const char *format, va_list argv);
int		ft_vsnprintf(char *str, size_t size, const char *format, va_list argv);
// Internal function
int		_ft_printf_internal(t_printf_data *data, va_list argv);
ssize_t	ft_printf_write(t_printf_output *out, const char *buffer, size_t size);

#endif
