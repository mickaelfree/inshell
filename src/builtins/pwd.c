/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:16 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/18 16:21:14 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"

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
