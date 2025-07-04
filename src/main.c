/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/27 16:39:30 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inshell.h"
void display_parsed_command(t_command *cmd)
{
    if (!cmd)
        return;
        
    printf("\n===== PARSING RESULT =====\n");
    
    // Afficher les arguments
    printf("- Arguments (%d):\n", cmd->arg_count);
    for (int i = 0; i < cmd->arg_count; i++)
        printf("  [%d]: '%s'\n", i, cmd->args[i]);
    
    // Afficher les redirections
    if (cmd->input_file)
        printf("- Input redirection: '%s'\n", cmd->input_file);
    if (cmd->output_file)
        printf("- Output redirection: '%s' (append: %d)\n", 
               cmd->output_file, cmd->append_mode);
    if (cmd->heredoc_delim)
        printf("- Heredoc delimiter: '%s'\n", cmd->heredoc_delim);
        
    printf("==========================\n\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	char	**new_env;
	t_command *cmd;

	// TODO: recuper les envp
	new_env = ft_env(envp);
	while (1)
	{
		line = readline("Inshell>");
		if (!line)
			break;
		add_history(line);
		
		// Parser la ligne et afficher les résultats
		cmd = parse_token(line);
		if (cmd)
		{
			// Afficher les résultats du parsing
			display_parsed_command(cmd);
			
			// Exécuter la commande avec les arguments parsés
			if (cmd->arg_count > 0)
			{
				if (!is_builtin(cmd->args, new_env))
					execute_cmd(cmd->args, new_env);
			}
			
		
                }
		free(line);
	}
	return (0);
}
