/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/27 16:38:52 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// TODO::
#include "../../includes/inshell.h"

int	builtin_unset(char **args, char **envp)
{
	int	i;
	int	found;

	if (!args[1])
		return (1);
	args++;
	while (*args)
	{
		i = 0;
		found = 0;
		while (envp[i])
		{
			found = !strcmp(envp[i], *args);
			if (found)
			{
				while (envp[i + 1])
				{
					envp[i] = envp[i + 1];
					i++;
				}
				envp[i] = NULL;
				break ;
			}
			i++;
		}
		args++;
	}
	return (0);
}
