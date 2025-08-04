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

    new_env = ft_env(envp);
    signal(SIGINT, ft_handle_sig);
    while (1)
    {
        line = readline("Inshell>");
        if (!line)
            ft_handle_ctrld();
        add_history(line);
        
        cmd = parse_token(line);
        if (cmd)
        {
            //display_parsed_command(cmd);

            if (cmd->arg_count > 0)
            {
                if (!is_builtin(cmd->args, &new_env))
                    execute_cmd(cmd, &new_env);
            }
            free_commands(cmd);
        }

        free(line);
    }
    return (0);
}
