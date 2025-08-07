/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/05 00:13:22 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inshell.h"
#include <stdlib.h>

void display_parsed_command(t_command *cmd)
{
    if (!cmd)
        return;
        
    printf("\n===== PARSING RESULT =====\n");
    
    printf("- Arguments (%d):\n", cmd->arg_count);
    for (int i = 0; i < cmd->arg_count; i++)
        printf("  [%d]: '%s'\n", i, cmd->args[i]);
    
    if (cmd->input_file)
        printf("- Input redirection: '%s'\n", cmd->input_file);
    if (cmd->output_file)
        printf("- Output redirection: '%s' (append: %d)\n", 
               cmd->output_file, cmd->append_mode);
    if (cmd->heredoc_delim)
        printf("- Heredoc delimiter: '%s'\n", cmd->heredoc_delim);
        
    printf("==========================\n\n");
}
void test_parsing()
{
    char *line = "ls -l | grep \"test file\" > output.txt >> append.txt << END";
    t_command *cmds = parse_token(line);
    if (!cmds)
        return;

    t_command *cur = cmds;
    while (cur)
    {
        printf("Command args: ");
        for (int i = 0; i < cur->arg_count; i++)
            printf("%s ", cur->args[i]);
        printf("\nInput: %s\nOutput: %s (append: %d)\nHeredoc: %s\n---\n",
               cur->input_file, cur->output_file, cur->append_mode, cur->heredoc_delim);
        cur = cur->next;
    }

    //free_commands(cmds);
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    char **new_env;
    t_command *cmd;
    int builtin_ret;


    builtin_ret =0;
    new_env = ft_env(envp);

    signal(SIGINT, ft_handle_sig);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        line = readline("Inshell>");
        if (!line)
            ft_handle_ctrld();
        if(*line)
                add_history(line);
        else
        {
                free(line);
                continue;
        }
        cmd = parse_token(line);
        if (cmd)
        {
            //display_parsed_command(cmd);

            if (cmd->arg_count > 0)
            {
             builtin_ret = is_builtin(cmd->args, &new_env);
                if (builtin_ret== -1)
                   execute_cmd(cmd, &new_env);
                else
                   g_last_exit_status = builtin_ret;
            }
            free_commands(cmd);
        }
        free(line);
    }
        if (new_env)
                free(new_env);
    return (0);
}
