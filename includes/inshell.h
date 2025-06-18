/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:12:48 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/17 19:18:31 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INSHELL_H
# define INSHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
//parsing
typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_QUOTED,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND,
} t_token_type;
///
typedef enum e_builtin_type {
        BUILTIN_ECHO,
        BUILTIN_CD,
        BUILTIN_EXIT,
        BUILTIN_ENV,
        BUILTIN_EXPORT,
        BUILTIN_PWD,
        BUILTIN_UNSET,
        BUILTIN_UNKNOWN,
} t_builtin_type;

typedef struct s_builtin_entry {
        const char *name;
        t_builtin_type type;
} t_builtin_entry;

typedef int (*builtin_func)(char **args, char **envp);

typedef struct s_pre_token
{ 
        char *start;
        int len;
        int type;
        struct s_pre_token *next;
}
t_pre_token;

void pre_token(char *line);
t_pre_token *tokenize_input(char *line);
void free_token_list(t_pre_token *head);

void	ft_error(char *msg);
void	ft_free(char **tab);
void	execute(char **av, char **env);
void	execute_cmd(char **av, char **env);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*find_path(char *cmd, char **env);
// TODO:
// la stuctur pour le parsing la tokenisation etc

int		builtin_echo(char **args,char **envp);
int		builtin_pwd(char **args,char **envp);
int		builtin_cd(char **args, char **envp);
int		builtin_env(char **args, char **envp);
int		builtin_export(char **args, char **envp);
int		builtin_unset(char **args, char **envp);
int	        builtin_exit(char **args,char **envp);

// INFO: header pour les utils

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t sz);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);

char  **ft_env(char **envp);
// INFO:
// ft_is
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);

#endif
