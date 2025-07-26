/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:12:48 by mickmart          #+#    #+#             */
/*   Updated: 2025/07/26 18:57:37 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define INSHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
// parsing
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
///
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
	char	**args;
	int	arg_count;
	char	*input_file;
	char	*output_file;
	char	*heredoc_delim;
	int	append_mode;
        struct s_command	*next;
}	t_command;

typedef int				(*builtin_func)(char **args, char **envp);

void					pre_token(char *line);
t_pre_token				*tokenize_input(char *line);
void					free_token_list(t_pre_token *head);

void					ft_error(char *msg);
void					ft_free(char **tab);
void					execute(char **av, char **env);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
char					*find_path(char *cmd, char **env);

int						builtin_echo(char **args, char **envp);
int						builtin_pwd(char **args, char **envp);
int						builtin_cd(char **args, char **envp);
int						builtin_env(char **args, char **envp);
int						builtin_export(char **args, char ***envp);
int						builtin_unset(char **args, char **envp);
int						builtin_exit(char **args, char **envp);
int						is_builtin(char **args, char ***envp);
void					skip_whitespace(char **line);

// INFO: header pour les utils

size_t					ft_strlen(const char *str);
size_t					ft_strlcpy(char *dst, const char *src, size_t sz);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_split(char const *s, char c);
char					*ft_strdup(const char *s);

char					**ft_env(char **envp);
// INFO:
// ft_is
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
// INFO:
// utils_parsr

void test_parsing();
t_pre_token				*add_new_token(t_pre_token **head,
							t_pre_token **current, char *start, int len,
							int type);

t_command *parse_token(char *line);
void					print_token(t_pre_token *token);
void					skip_whitespace(char **line);
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
t_pre_token				*identify_token(char *line);
t_command *build_pipeline(t_pre_token *tokens);
char *process_heredoc(char *delimiter);
void execute_cmd(t_command *cmds, char **envp);
void free_commands(t_command *head);

#endif
