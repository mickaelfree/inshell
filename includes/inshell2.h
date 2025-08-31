/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:12:48 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/31 00:55:30 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSHELL_H
# define INSHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Variable globale pour le status de sortie ($?)
extern int				g_last_exit_status;

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
}						t_char_type;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_QUOTED,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
}						t_token_type;

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
}						t_builtin_type;

typedef struct s_builtin_entry
{
	const char			*name;
	t_builtin_type		type;
}						t_builtin_entry;

typedef struct s_pre_token
{
	char				*start;
	int					len;
	int					type;
	struct s_pre_token	*next;
}						t_pre_token;

typedef struct s_command
{
	char				**args;
	int					arg_count;
	char				*input_file;
	char				*output_file;
	char				*heredoc_delim;
	int					append_mode;
	struct s_command	*next;
}						t_command;

typedef int				(*builtin_func)(char **args, char ***envp);

// Parsing functions
void					pre_token(char *line);
t_pre_token				*tokenize_input(char *line);
void					free_token_list(t_pre_token *head);
t_command				*parse_token(char *line, char **envp);
void					print_token(t_pre_token *token);
void					skip_whitespace(char **line);
t_pre_token				*identify_token(char *line);
t_command				*build_pipeline(t_pre_token *tokens, char **envp);
void					free_commands(t_command *head);
char					*get_env_value(char *name, char **envp);
int	update_env_var(char ***envp_ptr, char *var);
// Expansion functions
char					*expand_env(char *name);
char					*expand_variables(char *str, char **envp);
char					*expand_token(char *token, int is_quoted);

// Execution functions
void					ft_error(char *msg);
void					ft_free(char **tab);
void					execute(char **av, char **env);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
char					*find_path(char *cmd, char **env);
char					*process_heredoc(char *delimiter);
void					execute_cmd(t_command *cmds, char ***envp);

// Builtin functions
int						builtin_echo(char **args, char ***envp);
int						builtin_pwd(char **args, char ***envp);
int						builtin_cd(char **args, char ***envp);
int						builtin_env(char **args, char ***envp);
int						builtin_export(char **args, char ***envp);
int						builtin_unset(char **args, char ***envp);
int						builtin_exit(char **args, char ***envp);
int						is_builtin(char **args, char ***envp);

// String utilities
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *str);
size_t					ft_strlcpy(char *dst, const char *src, size_t sz);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_split(char const *s, char c);
char					*ft_strdup(const char *s);
char					*ft_strcpy(char *dst, const char *src);
char					**ft_env(char **envp);

// Character check functions
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);

// Token identification helpers
void					test_parsing(void);
t_pre_token				*add_new_token(t_pre_token **head,
							t_pre_token **current, char *start, int len,
							int type);
int						char_type(char *c);
int						is_whitespace(char c);
int						is_operator(char c);
int						is_pipe(char c);
int						is_redir(char c);
int						is_append(char *c);
int						is_heredoc(char *c);
int						is_single_quote(char c);
int						is_double_quote(char c);
int						is_escape(char c);
int						is_quote(char c);
int						is_special(char c);

// Signal handlers
void					ft_handle_ctrld(void);
void					ft_handle_sig(int sig);

#endif
