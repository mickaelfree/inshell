/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:38:21 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 19:40:40 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WRITE_H
# define FT_WRITE_H

/** @name FT_PUTCHAR_FD**
** @brief The ft_putchar_fd() function writes the
character c on the file descriptor fd.
**
** @param c: character to write.
** @param fd: file descriptor on which to write.
** @return none.
*/
void				ft_putchar_fd(char c, int fd);

/** @name FT_PUTENDL_FD**
** @brief write the string s, followed by a newline,
on the file descriptor fd.
**
** @param s: string to display.
** @param fd: file descriptor on which to write.
** @return none.
*/
void				ft_putendl_fd(char *s, int fd);

/** @name FT_PUTNBR_FD**
** @brief write the int n on the file descriptor fd.
**
** @param n: int to write.
** @param fd: file descriptor on which to write.
** @return none.
*/
void				ft_putnbr_fd(int n, int fd);

/** @name FT_PUTSTR_FD**
** @brief Write a function that displays a string on the standard output.
**
** @param s: string to display.
** @param fd: file descriptor on which to write.
** @return none.
*/
void				ft_putstr_fd(char *s, int fd);

#endif