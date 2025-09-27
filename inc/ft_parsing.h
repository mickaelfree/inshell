/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 23:56:13 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 00:26:32 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

#include<ft_structs.h>

//build_pipeline.c
void						init_command(t_command *cmd);
void						add_argument(t_command *cmd, char *value,
								char **envp);
t_command					*build_pipeline(t_pre_token *tokens, char **envp);

//can_token.c
int							can_handle_pipe(t_pre_token *token);
int							can_handle_redirection(t_pre_token *token);
int							can_handle_word(t_pre_token *token);
//expand_env.c
char						*expand_variables(char *str, char **envp);

//expand_quoted.c
char						*expand_variables_with_quote(char *str,
								char **envp);

//expand_sizer.c
size_t						calculate_expanded_size(char *str, char **envp);

//expand_utils.c
char						*get_env_value(char *name, char **envp);
char						*expand_env(char *name);
char						*trim_leading_spaces(char *result);

//handle_token.c
int							process_token(t_pre_token **token,
								t_command **current, t_command **head,
								char **envp);

//identify_token.c
t_pre_token					*identify_token(char *line);

//parsing.c
t_command					*parse_token(char *line, char **envp);

// quote_handler.c
char						*remove_quotes(char *token, int len);
int							check_for_quotes(t_pre_token **head, char **ptr);

//redirection_handler.c
int							handle_redirection(t_command *cmd,
								t_pre_token **token, char **envp);

//redirection_utils.c
int							create_and_add_redirection(t_command *cmd, int type,
								char *filename);

// token_utils.c
t_pre_token					*add_type_token(t_pre_token **head,
								t_pre_token **current, char **start, int type);
t_pre_token					*add_word_token(t_pre_token **head,
								t_pre_token **current, char *start, int len);

#endif