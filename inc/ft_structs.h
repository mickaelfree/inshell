/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:30:07 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 02:47:06 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

# include <ft_enum.h>
# include <sys/ioctl.h>
# include <sys/types.h>

typedef struct s_pipeline
{
	pid_t					*pids;
	int						(*pipes)[2];
	int						cmd_count;
	int						pipe_count;
}							t_pipeline;

typedef struct s_builtin_entry
{
	const char				*name;
	t_builtin_type			type;
}							t_builtin_entry;

typedef struct s_pre_token
{
	char					*start;
	int						len;
	int						type;
	struct s_pre_token		*next;
}							t_pre_token;

typedef struct s_redirection
{
	int						type;
	char					*filename;
	int						append_mode;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char					**args;
	int						arg_count;
	char					*input_file;
	char					*output_file;
	char					*heredoc_delim;
	int						append_mode;
	t_redirection			*redirections;
	struct s_command		*next;
}							t_command;

typedef struct s_expand_ctx
{
	char					*result;
	char					**envp;
	int						j;
}							t_expand_ctx;

typedef struct s_quote_ctx
{
	char					*str;
	char					*result;
	char					**envp;
	size_t					i;
	size_t					start;
	int						in_single;
	int						in_double;
}							t_quote_ctx;

typedef struct s_child_ctx
{
	t_command				*head;
	t_command				*cmd;
	int						index;
	t_pipeline				*pipeline;
	char					***envp;
}							t_child_ctx;

typedef int					(*t_redir_fn)(t_redirection *r);

typedef int					(*t_builtin_func)(t_command *cmd, char **args,
						char ***envp);

typedef struct s_redir_entry
{
	int						type;
	t_redir_fn				fn;
}							t_redir_entry;

typedef struct s_token_handler
{
	int						(*can_handle)(t_pre_token *token);
	int						(*handle)(t_command **current, t_pre_token **token,
			char **envp, t_command **head);
}							t_token_handler;

#endif
