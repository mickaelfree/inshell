/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:34 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/25 13:20:33 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// INCLUDES
# include <stdint.h>
# include <stdbool.h>

# include "ft_printf.h"
# include "libft.h"

// PROTOTYPES
// IO
int				ft_printf_write_hex(t_printf_output *out, uint64_t n, \
										int padding, bool upper);
int				ft_printf_write_ll(t_printf_output *out, int64_t n, \
										int padding, bool write_sign);
int				ft_printf_write_llu(t_printf_output *out, uint64_t n, \
										int padding);
int				ft_printf_pad(t_printf_output *out, char c, int padding);

// Conversion
int				int_strlen(int64_t n, int base, bool count_sign);
int				uint_strlen(uint64_t n, int base);
unsigned int	ft_strtoui(char *nptr, char **endptr);

#endif
