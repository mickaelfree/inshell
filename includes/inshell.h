/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:12:48 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/05 04:41:16 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INSHELL_H
# define INSHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
//pipex
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

void	ft_error(char *msg);
void	ft_free(char **tab);
size_t	ft_strlen(const char *str);
void	execute(char **av, char **env);
void	execute_cmd(char **av, char **env);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*find_path(char *cmd, char **env);
size_t	ft_strlcpy(char *dst, const char *src, size_t sz);
char	*ft_strjoin(char const *s1, char const *s2);
//pipex
// TODO:
// la stuctur pour le parsing la tokenisation etc

int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_cd(char **args, char **envp);
int		builtin_env(char **args, char **envp);
int		builtin_export(char **args, char **envp);
int		builtin_unset(char **args, char **envp);
void	builtin_exit(char **args);

// INFO: header pour les utils

size_t	ft_strlcpy(char *dst, const char *src, size_t sz);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);

// INFO:
// ft_is
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);

#endif
