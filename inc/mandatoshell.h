/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatoshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:21:13 by zsonie            #+#    #+#             */
/*   Updated: 2025/10/01 00:18:20 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATOSHELL_H
# define MANDATOSHELL_H

# include <ft_enum.h>
# include <ft_structs.h>

# ifndef NB_REDIRS_FUNC
#  define NB_REDIRS_FUNC 3
# endif

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# ifndef TESTER
#  define TESTER 0
# endif

extern int	g_last_exit_status;

void		execute_cmd(t_command *cmds, char ***envp);
int			execute_child(t_child_ctx *ctx);
void		execute(t_child_ctx ctx);
void		cleanup_path_and_ctx(char *path, t_child_ctx ctx, int exit_code);
void		handle_error_ctx(char *patch, int status, t_child_ctx ctx);
char		*find_path(char *cmd, char **env, t_child_ctx _ctx);
char		*process_heredoc(char *delimiter);
void		execute_pipe(t_command *cmds, int cmd_count, char ***envp);
int			count_pipeline(t_command *cmds);
t_pipeline	*create_pipeline(int cmd_count);
void		destroy_pipeline(t_pipeline *pipeline);
int			setup_pipes(t_pipeline *pipeline);
int			setup_child_pipes(int index, t_pipeline *pipeline);
void		close_parent_pipes(t_pipeline *pipeline);
int			exec_redirections(t_command *cmd, int saved_stdin);
void		init_redir_table(t_redir_entry *func);

#endif
