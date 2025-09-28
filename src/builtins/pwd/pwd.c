/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:16 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 01:56:20 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

int	builtin_pwd(t_command *cmd, char **argv, char ***envp)
{
	char	*line;

	(void)cmd;
	(void)argv;
	(void)envp;
	line = NULL;
	line = getcwd(line, 0);
	if (!line)
		return (EXIT_FAILURE);
	printf("%s\n", line);
	free(line);
	return (EXIT_SUCCESS);
}
