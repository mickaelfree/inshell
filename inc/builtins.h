/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 23:31:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 02:43:55 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <ft_structs.h>
// cd.c
int		builtin_cd(t_command *cmd, char **args, char ***envp);

// echo.c
int		builtin_echo(t_command *cmd, char **args, char ***envp);

// env.c
char	**init_env(char ***envp);
int		builtin_env(t_command *cmd, char **args, char ***envp);

// exit.c
int		builtin_exit(t_command *cmd, char **args, char ***envp);

// export.c
int		update_env_var(char ***envp_ptr, char *var);
int		builtin_export(t_command *cmd, char **args, char ***envp);

// is_builin.c
int		is_builtin(char **args);
int		execute_builtin(t_command *cmd, char ***envp);

// pwd.c
int		builtin_pwd(t_command *cmd, char **args, char ***envp);

// unset.c
int		builtin_unset(t_command *cmd, char **args, char ***envp);

#endif