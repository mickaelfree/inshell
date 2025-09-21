/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 07:35:32 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 18:45:56 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/////////////////////////////////////////////////////
//----------------------------------INCLUDE----------------------------------//
/////////////////////////////////////////////////////
# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

/////////////////////////////////////////////////////
//------------------------------------VAR------------------------------------//
/////////////////////////////////////////////////////

int		ft_printf(const char *str, ...);
int		ft_printf_parse(char current, va_list ptr, size_t *fsize);
void	ft_putnbr_base_ul(unsigned long nbr, char *base, int fd, size_t *fsize);
void	ft_putnbr_int(int n, int fd, size_t *fsize);

#endif