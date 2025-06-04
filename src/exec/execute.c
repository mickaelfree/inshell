/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:20:51 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/05 01:05:22 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

// void	create_processes(char **av, char **env, int *fd, int *status)
// {
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		status1;
//
// 	pid1 = fork();
// 	if (pid1 == -1)
// 		clean_exit("fork failed", fd[0], fd[1]);
// 	if (pid1 == 0)
// 		child_process(av, env, fd);
// 	pid2 = fork();
// 	if (pid2 == -1)
// 		clean_exit("fork failed", fd[0], fd[1]);
// 	if (pid2 == 0)
// 		child_process2(av, env, fd);
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, &status1, 0);
// 	waitpid(pid2, status, 0);
// }
 
void execute(char **args, char **envp)
{
        (void)envp;
    int cmd_count = 0;
    char **cmd;
    int i = 0;
    
    // INFO:Compter le nombre de commandes
        i = 0;
        while (args[i])
        {
            cmd_count++;
            i++;
        }
        cmd = malloc (sizeof(char *) * (cmd_count + 1));
        i = 0;
        while (args[i])
        {
            cmd[i] = ft_strdup(args[i]);
            if (!cmd[i])
            {
                perror("malloc");
                return;
            }
            i++;
        }
        cmd[i] = NULL;

     while (cmd[i])
    {
        printf("cmd[%d]: %s\n", i, cmd[i]);
        cmd_count++;
        i++;
    }
    
    printf("Parent process PID: %d\n", getpid());
    printf("Total commands: %d\n", cmd_count);
    
    // INFO:Créer les pipes et les processus
    int pipes[cmd_count-1][2];
    pid_t pids[cmd_count];
    
    // INFO:Créer les pipes
    i = 0;
    while(i < cmd_count-1)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return;
        }
                i++;
    }
    //INFO: Créer les processus
        i = 0;
    while(i < cmd_count)
    {
        pids[i] = fork();
        
        if (pids[i] < 0)
        {
            perror("fork");
            return;
        }
        else if (pids[i] == 0)
        {
            //INFO: Processus enfant
            printf("Child process %d (PID: %d, PPID: %d) executing: %s\n", 
                   i+1, getpid(), getppid(), cmd[i]);
            
            //INFO: Logique de redirection à implémenter ici
                char *test_cmd[4]; 
                test_cmd[0] = "/bin/echo";
                test_cmd[1] =    "Je suis le processus";
                test_cmd[2] =    cmd[i];
                test_cmd[3] =    NULL;
                execve(test_cmd[0], test_cmd, envp);
        }
                i++;
    }
    i = 0;
        //INFO: Fermer tous les pipes dans le processus parent
    while( i < cmd_count-1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
                i++;
    }
    // INFO:Attendre tous les processus enfants
    i = 0;
    while( i < cmd_count)
    {
        int status;
        printf("Waiting for child process %d (PID: %d)\n", i+1, pids[i]);
        waitpid(pids[i], &status, 0);
        printf("Child process %d (PID: %d) exited with status: %d\n", 
               i+1, pids[i], WEXITSTATUS(status));
        i++;
    }
}
