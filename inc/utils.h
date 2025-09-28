/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:29:03 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 02:47:19 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <ft_structs.h>

// DIRECTORY skip
char			*skip_charset(char *str, char charset);
void			skip_whitespace(char **line);

// char_utils.c
int				char_type(char *c);
char			*get_key(char *var);

// debug.c
void			print_token(t_pre_token *token);
void			display_parsed_command(t_command *cmd);

// ft_error.c
void			error_exit(void);
void			ft_error(char *msg);
void			export_error(char *arg);
char			*cd_err(const char *msg, int status);

// ft_free.c
void			ft_free(char **arr);
void			ft_free_commands(t_command *head);
void			ft_free_env(char **env);
void			ft_free_token_list(t_pre_token *head);
void			ft_free_args_and_redir(t_command *current);

// utils.c
unsigned int	ft_count(void **ptrs);
void			ft_free_tab(void **ptrs);
int				error_alloc(char *ptr, char **ptrs);
void			ft_free_ctx(t_quote_ctx *ctx);

#endif