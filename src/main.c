/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/20 18:00:04 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inshell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	char	**new_env;

	// TODO: recuper les envp
	new_env = ft_env(envp);
	while (1)
	{
		line = readline("Inshell>");
		if (!line)
			break ;
		add_history(line);
		pre_token(line);
		args = ft_split(line, ' ');
		if (!is_builtin(args, new_env))
			execute_cmd(args, new_env);
		// printf("args: %s\n", args[0]);
		// printf("args: %s\n", args[1]);
		// exec(line);
		free(line);
	}
	return (0);
}
