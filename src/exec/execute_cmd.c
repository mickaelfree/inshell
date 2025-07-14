/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:20:51 by mickmart          #+#    #+#             */
/*   Updated: 2025/07/01 21:00:11 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

                /*on cree les processus enfants 
                pour le premier 
                parent
                []
                while(n)    [stdin]
                ||=fork()-> cmd
                ||          || pipe
                ||=fork()-> cmd
                ||          || pipe
                ||=fork()-> cmd
                ||          || pipe
                            [stdout]
                */

static int count_pipeline(t_command *cmds)
{
    int count = 0;
    t_command *cur = cmds;
    while (cur)
    {
        count++;
        cur = cur->next;
    }
    return count;
}
static void handle_redirections(t_command *cmd)
{
    if (cmd->heredoc_delim)
    {
        cmd->input_file = process_heredoc(cmd->heredoc_delim);  // Crée tmp file
        if (!cmd->input_file)
            exit(1);  // Erreur
    }

    if (cmd->input_file)
    {
        int fd = open(cmd->input_file, O_RDONLY);
        if (fd == -1)
        {
            perror("open input");
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        if (cmd->heredoc_delim)  // Supprime tmp après open
            unlink(cmd->input_file);
    }

    if (cmd->output_file)
    {
        int flags = O_WRONLY | O_CREAT | (cmd->append_mode ? O_APPEND : O_TRUNC);
        int fd = open(cmd->output_file, flags, 0644);
        if (fd == -1)
        {
            perror("open output");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void execute_cmd(t_command *cmds, char **envp)
{
    int cmd_count = count_pipeline(cmds);
    if (cmd_count == 0)
        return;

    int pipes[cmd_count - 1][2];
    pid_t pids[cmd_count];
    t_command *cur = cmds;
    int i = 0;

    // Créer pipes
    for (i = 0; i < cmd_count - 1; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return;
        }
    }

    // Fork pour chaque cmd
    i = 0;
    while (cur)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            return;
        }
        else if (pids[i] == 0)  // Child
        {
            // Gérer pipes
            if (i > 0)  // Input from previous pipe
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);
                close(pipes[i - 1][1]);
            }
            if (i < cmd_count - 1)  // Output to next pipe
            {
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][0]);
                close(pipes[i][1]);
            }

            // Fermer tous les autres pipes
            for (int j = 0; j < cmd_count - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Gérer redirs (overwrites pipes si présent)
            handle_redirections(cur);

            // Exécuter
            if (cur->arg_count > 0)
            {
                if (is_builtin(cur->args, envp) == 0)  // Si pas builtin
                    execute(cur->args, envp);  // Ton execute pour externe
            }
            exit(0);  // Si rien
        }

        cur = cur->next;
        i++;
    }

    // Parent ferme pipes
    for (i = 0; i < cmd_count - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait enfants
    for (i = 0; i < cmd_count; i++)
    {
        int status;
        waitpid(pids[i], &status, 0);
    }
}
