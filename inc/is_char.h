/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_char.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:23:36 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 00:27:38 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CHAR_H
# define IS_CHAR_H

// DIRECTORY is_char
int	is_append(char *c);
int	is_double_quote(char c);
int	is_escape(char c);
int	is_heredoc(char *c);
int	is_operator(char c);
int	is_pipe(char c);
int	is_quote(char c);
int	is_redir(char c);
int	is_single_quote(char c);
int	is_special(char c);
int	is_whitespace(char c);

#endif