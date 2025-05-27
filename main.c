/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/27 16:15:26 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/inshell.h"

int is_builtin(char **args, char **envp)
{
	if (!strcmp(args[0], "echo"))
			builtin_echo(args);
	if (!strcmp(args[0], "pwd"))
			builtin_pwd();
	if (!strcmp(args[0], "env"))
			builtin_env(args,envp);
	if (!strcmp(args[0], "export"))
			builtin_export(args,envp);
	if (!strcmp(args[0], "unset"))
			builtin_unset(args,envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;

	// TODO:
	while (1)
	{
		line = readline("Inshell>");
		if (!line)
			break ;
		add_history(line);
		//printf(" %s\n", line);
		args = ft_split(line, ' ');
                is_builtin(args, envp);
		printf("args: %s\n", args[0]);
		printf("args: %s\n", args[1]);
		// exec(line);
		free(line);
	}
	return (0);
}
