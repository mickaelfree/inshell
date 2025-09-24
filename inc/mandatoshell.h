/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatoshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:21:13 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/24 03:24:01 by zsonie           ###   ########lyon.fr   */
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

# define NB_REDIRS_FUNC 3
# define AST_WORD 0
# define AST_CMD 1
# define AST_REDIRECT 2
# define AST_PIPE 3
# define AST_END 4

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

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
typedef struct s_ast
{
	char					*token;
	int						type;
	int						priority;
	void					(*exec)(void *, void *);
	struct s_ast			*left;
	struct s_ast			*right;
}							t_ast;

typedef struct s_pipeline
{
	pid_t					*pids;
	int (*pipes)[2];
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

/////////////////////////FUNCTIONS////////////////////////

//-----------------------------BUILTINS----------------------------//
int							builtin_echo(char **args, char ***envp);
int							builtin_pwd(char **args, char ***envp);
int							builtin_cd(char **args, char ***envp);
int							builtin_env(char **args, char ***envp);
int							builtin_export(char **args, char ***envp);
int							builtin_unset(char **args, char ***envp);
int							builtin_exit(char **args, char ***envp);
int							is_builtin(char **args);

//-------------------------------EXEC------------------------------//
void						execute_ast(t_ast *ast, char ***envp);
void						execute_node(t_ast *node, char ***envp);

//---------------------------OLD-PARSING---------------------------//

// TOKEN UTILS
void						skip_whitespace(char **line);
t_pre_token					*add_new_token(t_pre_token **head,
								t_pre_token **current, char *start, int len,
								int type);
int							char_type(char *c);

//-----------------------------PARSING-----------------------------//

char						**ast_to_args(t_ast *root);
void						print_doublechar(char **args);
char						*remove_quotes(char *token, int len);
// AST_UTILS
void						*set_exec_to_node(t_ast *node);
void						set_word_or_cmd_type(t_ast *node,
								int is_command_position);
void						set_command_arguments(t_ast *node);
void						clear_token_quotes(char **token);

// AST
t_ast						*generate_ast(char **tokens);
t_ast						*create_node(char *token);
t_ast						*add_node_to_tree(t_ast *tree, t_ast *node);
t_ast						*add_redir_or_pipe(t_ast *res, t_ast *node);

char						*split_to_tokens(char *input, char ***arr_tokens);
char						**realloc_list(char **ptr, size_t newsize);
void						add_elem_to_list(char ***lst, char *string);
char						*add_token(char ***arr_tokens, char *input,
								char *start, char *end);
char						*skip_charset(char *str, char charset);

//-----------------------------SIGNAL------------------------------//
void						ft_handle_ctrld(void);
void						ft_handle_sig(int sig);

//------------------------------UTILS------------------------------//
// AST DEBUG
void						print_ast(const t_ast *node, const char *prefix,
								int is_left);

// ERROR
void						error_exit(void);
void						ft_error(char *msg);
void						export_error(char *arg);
char						*cd_err(const char *msg, int status);

// init_env
char						**init_env(char ***envp);

// UTILS
char						*get_key(char *var);
unsigned int				ft_count(void **ptrs);
int							error_alloc(char *ptr, char **ptrs);
void						ft_free_tab(void **ptrs);
void						ft_free(char **arr);
void						ft_free_ast(t_ast *node);
void						ft_free_env(char **env);
void						ft_free_commands(t_command *head);
void						free_args_and_redir(t_command *current);
void						display_parsed_command(t_command *cmd);

void						clear_token_quotes(char **token);
void						concatenate_argument_to_cmd(t_ast *cmd_node,
								char *new_arg);

//------------MERGING(WIP)-----------------------------
// GLOBALS (To check if it's needed since we can use errno)
extern int					g_last_exit_status;

typedef int					(*builtin_func)(char **args, char ***envp);

// Parsing functions

size_t						calculate_expanded_size(char *str, char **envp);
void						pre_token(char *line);
t_pre_token					*tokenize_input(char *line);
void						free_token_list(t_pre_token *head);
t_command					*parse_token(char *line, char **envp);
void						print_token(t_pre_token *token);
char						*trim_leading_spaces(char *result);
int							can_handle_word(t_pre_token *token);
int							can_handle_pipe(t_pre_token *token);
int							can_handle_redirection(t_pre_token *token);
void						add_argument(t_command *cmd, char *value,
								char **envp);
char						*expand_variables_with_quote(char *str, char **envp,
								int quote_type);
int							handle_redirection(t_command *cmd,
								t_pre_token **token, char **envp);
void						init_command(t_command *cmd);
int							process_token(t_pre_token **token,
								t_command **current, t_command **head,
								char **envp);
int							create_and_add_redirection(t_command *cmd, int type,
								char *filename);

t_pre_token					*identify_token(char *line);
t_command					*build_pipeline(t_pre_token *tokens, char **envp);
char						*get_env_value(char *name, char **envp);
int							update_env_var(char ***envp_ptr, char *var);
// Expansion functions
char						*expand_env(char *name);
char						*expand_variables(char *str, char **envp);
char						*expand_token(char *token, int is_quoted);

// Execution functions
void						ft_error(char *msg);
void						execute(char **av, char **env);
char						*find_path(char *cmd, char **env);
char						*process_heredoc(char *delimiter);
void						execute_cmd(t_command *cmds, char ***envp);
int							execute_builtin(char **args, char ***envp);
// redirections

void						init_redir_table(t_redir_entry *func);
int							handle_redirections(t_command *cmd);

void						execute_pipeline(t_command *cmds, int cmd_count,
								char ***envp);
int							count_pipeline(t_command *cmds);
t_pipeline					*create_pipeline(int cmd_count);
void						destroy_pipeline(t_pipeline *pipeline);
int							setup_pipes(t_pipeline *pipeline);
void						close_parent_pipes(t_pipeline *pipeline);

// Token identification helpers
void						test_parsing(void);

int							is_whitespace(char c);
int							is_operator(char c);
int							is_pipe(char c);
int							is_redir(char c);
int							is_append(char *c);
int							is_heredoc(char *c);
int							is_single_quote(char c);
int							is_double_quote(char c);
int							is_escape(char c);
int							is_quote(char c);
int							is_special(char c);

#endif
