/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 23:31:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 07:03:22 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# include <ft_structs.h>

int				builtin_cd(t_command *cmd, char **args, char ***envp);
int				builtin_echo(t_command *cmd, char **args, char ***envp);
int				builtin_env(t_command *cmd, char **args, char ***envp);
char			**init_env(char ***envp);
int				builtin_exit(t_command *cmd, char **args, char ***envp);
int				builtin_export(t_command *cmd, char **args, char ***envp);
int				update_env_var(char ***envp_ptr, char *var);
int				builtin_pwd(t_command *cmd, char **args, char ***envp);
int				builtin_unset(t_command *cmd, char **args, char ***envp);

int				is_builtin(char **args);
int				execute_builtin(t_command *cmd, char ***envp);
t_builtin_type	get_builtin_type(char *cmd);

#endif