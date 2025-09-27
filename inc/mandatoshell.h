/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatoshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:21:13 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 00:27:14 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATOSHELL_H
# define MANDATOSHELL_H

// INCLUDES
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <ft_structs.h>
# include <ft_enum.h>

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

/////////////////////////FUNCTIONS////////////////////////

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


//-----------------------------SIGNAL------------------------------//

#endif
