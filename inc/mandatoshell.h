/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatoshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:21:13 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/25 17:03:25 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATOSHELL_H
# define MANDATOSHELL_H

// INCLUDES
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

/////////////////////////MACRO////////////////////////

# ifndef NB_REDIRS_FUNC
#  define NB_REDIRS_FUNC 3
# endif

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# ifndef TESTER
#  define TESTER 0
# endif

extern int					g_last_exit_status;

/////////////////////////ENUMS////////////////////////

typedef enum e_char_type
{
	CHAR_NORMAL,
	CHAR_WHITESPACE,
	CHAR_PIPE,
	CHAR_REDIR,
	CHAR_APPEND,
	CHAR_HEREDOC,
	CHAR_SINGLE_QUOTE,
	CHAR_DOUBLE_QUOTE,
	CHAR_ESCAPE,
	CHAR_SPECIAL,
}							t_char_type;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_QUOTED,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
}							t_token_type;

typedef enum e_builtin_type
{
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_EXIT,
	BUILTIN_ENV,
	BUILTIN_EXPORT,
	BUILTIN_PWD,
	BUILTIN_UNSET,
	BUILTIN_UNKNOWN,
}							t_builtin_type;

/////////////////////////STRUCTS////////////////////////

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

typedef int					(*t_redir_fn)(t_redirection *r);

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

typedef int					(*t_builtin_func)(t_command *cmd, char **args, char ***envp);

/////////////////////////FUNCTIONS////////////////////////

//-----------------------------BUILTINS----------------------------//

//cd.c
int							builtin_cd(t_command *cmd, char **args, char ***envp);

//echo.c
int							builtin_echo(t_command *cmd, char **args, char ***envp);

//env.c
char						**init_env(char ***envp);
int							builtin_env(t_command *cmd, char **args, char ***envp);

//exit.c
int							builtin_exit(t_command *cmd, char **args, char ***envp);

//export.c
int							update_env_var(char ***envp_ptr, char *var);
int							builtin_export(t_command *cmd, char **args, char ***envp);

//is_builin.c
int							is_builtin(char **args);
int							execute_builtin(t_command *cmd, char ***envp);

//pwd.c
int							builtin_pwd(t_command *cmd, char **args, char ***envp);

//unset.c
int							builtin_unset(t_command *cmd, char **args, char ***envp);

//-------------------------------EXEC------------------------------//

//execute_cmd.c
void						execute_cmd(t_command *cmds, char ***envp);

//execute.c
void						execute(char **av, char **env);

//find_path.c
char						*find_path(char *cmd, char **env);

//heredoc.c
char						*process_heredoc(char *delimiter);

//pipeline_exec.c
void						execute_pipeline(t_command *cmds, int cmd_count,
								char ***envp);

//pipeline_utils.c
int							count_pipeline(t_command *cmds);
t_pipeline					*create_pipeline(int cmd_count);
void						destroy_pipeline(t_pipeline *pipeline);
int							setup_pipes(t_pipeline *pipeline);
void						close_parent_pipes(t_pipeline *pipeline);

//redirections.c
int							handle_redirections_exec(t_command *cmd);

//utils_redir.c
void						init_redir_table(t_redir_entry *func);

//-----------------------------PARSING-----------------------------//

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

//-----------------------------SIGNAL------------------------------//

//handler.c
void						ft_handle_ctrld(void);
void						ft_handle_sig(int sig);

//------------------------------UTILS------------------------------//

//char_utils.c
int							is_operator(char c);
void						skip_whitespace(char **line);
char						*skip_charset(char *str, char charset);
int							char_type(char *c);
char						*get_key(char *var);

//debug.c
void						print_token(t_pre_token *token);
void						display_parsed_command(t_command *cmd);

//ft_error.c
void						error_exit(void);
void						ft_error(char *msg);
void						export_error(char *arg);
char						*cd_err(const char *msg, int status);

//ft_free.c
void						ft_free(char **arr);
void						ft_free_commands(t_command *head);
void						ft_free_env(char **env);
void						free_token_list(t_pre_token *head);
void						free_args_and_redir(t_command *current);

//is_char.c
int							is_escape(char c);
int							is_quote(char c);
int							is_double_quote(char c);
int							is_single_quote(char c);
int							is_special(char c);

//is_type.c
int							is_whitespace(char c);
int							is_pipe(char c);
int							is_redir(char c);
int							is_append(char *c);
int							is_heredoc(char *c);

//utils.c
unsigned int				ft_count(void **ptrs);
void						ft_free_tab(void **ptrs);
int							error_alloc(char *ptr, char **ptrs);
void						ft_free_ctx(t_quote_ctx *ctx);

#endif
