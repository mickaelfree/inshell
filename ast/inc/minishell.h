
#ifndef MINISHELL_H
# define MINISHELL_H

//INCLUDES
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
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

/////////////////////////MACRO////////////////////////

# define AST_WORD 0
# define AST_REDIRECT 1
# define AST_PIPE 2
# define AST_END 3

/////////////////////////STRUCTS////////////////////////
typedef struct s_ast
{
	char			*token;
	int				type;
	int				priority;
	void			(*exec)();
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/////////////////////////FUNCTIONS////////////////////////
//AST
t_ast				*generate_ast(char **tokens);
t_ast				*create_node(char *token);
t_ast				*add_node_to_tree(t_ast *tree, t_ast *node);
t_ast				*add_redir_or_pipe(t_ast *res, t_ast *node);

//EXEC
void				exec_builtin(char *command, char **args);
int					ft_pwd(void);
int					ft_echo(char **args);

//PARSING
char				*split_to_tokens(char *input, char ***arr_tokens);
char				**realloc_list(char **ptr, size_t newsize);
void				add_elem_to_list(char ***lst, char *string);
char				*add_token(char ***arr_tokens, char *input, char *start,
						char *end);
char				*skip_charset(char *str, char charset);

//AST DEBUG
void				print_ast(const t_ast *node, const char *prefix,
						int is_left);

//ERRORS
void				error_exit(void);

//UTILS
char				**free_arr(char **arr);

#endif