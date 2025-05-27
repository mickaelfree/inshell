/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/27 16:03:19 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// TODO::
#include "../../includes/inshell.h"

int	builtin_unset(char **args, char **envp)
{
	int	i;

	if (!args[1])
		return (1);
	args++;
	while (*args)
	{
		i = 1;
		while (envp[i])
		{
			if (!strcmp(envp[i], *args))
			{
				free(envp[i]);
				while (envp[i + 1])
				{
					envp[i] = envp[i + 1];
					i++;
				}
				envp[i] = NULL;
			}
			i++;
		}
		args++;
	}
	return (0);
}
