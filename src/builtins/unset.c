/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/27 16:01:35 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// TODO::
#include "../../includes/inshell.h"

int	builtin_unset(char **args, char **envp)
{
	int	i;
	int	j;

	if (!args[1])
		return (1);
	args++;
	while (*args)
	{
		i = 0;
		while (envp[i])
		{
			if (!strcmp(envp[i], *args))
			{
				free(envp[i]);
				j = i;
				while (envp[j + 1])
				{
					envp[j] = envp[j + 1];
					j++;
				}
				envp[j] = NULL;
			}
			else
				i++;
		}
		args++;
	}
	return (0);
}
