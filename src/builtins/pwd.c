/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:16 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 22:01:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

int	builtin_pwd(void)
{
	char	*line;

	line = NULL;
	line = getcwd(line, 0);
	if (!line)
		return (EXIT_FAILURE);
	printf("%s\n", line);
	free(line);
	return (EXIT_SUCCESS);
}
