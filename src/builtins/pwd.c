/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:16 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/06 20:23:50 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

int	builtin_pwd(char **argv, char ***envp)
{
	char	*line;

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
