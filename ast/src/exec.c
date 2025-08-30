/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:32:31 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/30 19:34:42 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	exec_builtin(char *command, char **args)
{
	int	i;

	i = 0;
	while (command[i])
	{
		command[i] = ft_tolower(command[i]);
		i++;
	}
	if (ft_strncmp(command, "echo", 4) == 0)
		ft_echo(args);
	else if (ft_strncmp(command, "pwd", 3) == 0)
		ft_pwd();
	// This function will execute built-in commands like echo, cd, pwd, etc.
	// It will check the command and call the appropriate function.
	// For example:
	// if (ft_strcmp(command, "echo") == 0)
	//     ft_echo(args);
	// else if (ft_strcmp(command, "cd") == 0)
	//     ft_cd(args);
	// else if (ft_strcmp(command, "pwd") == 0)
	//     ft_pwd();
	// Add more built-in commands as needed.
}
