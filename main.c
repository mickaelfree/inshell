/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/05 04:34:29 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/inshell.h"

int	is_builtin(char **args, char **envp)
{
	if (!strcmp(args[0], "echo"))
	{
		builtin_echo(args);
		return (1);
	}
	if (!strcmp(args[0], "pwd"))
	{
		builtin_pwd();
		return (1);
	}
	if (!strcmp(args[0], "cd"))
	{
		builtin_cd(args, envp);
		return (1);
	}
	if (!strcmp(args[0], "env"))
	{
		builtin_env(args, envp);
		return (1);
	}
	if (!strcmp(args[0], "export"))
	{
		builtin_export(args, envp);
		return (1);
	}
	if (!strcmp(args[0], "unset"))
	{
		builtin_unset(args, envp);
		return (1);
	}
	if (!strcmp(args[0], "exit"))
	{
		builtin_exit(args);
		return (1);
	}
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
		args = ft_split(line, ' ');
		if(!is_builtin(args, envp))
                        execute_cmd(args, envp);
		//printf("args: %s\n", args[0]);
		//printf("args: %s\n", args[1]);
		// exec(line);
		free(line);
	}
	return (0);
}
