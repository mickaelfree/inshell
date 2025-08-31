/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:41 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/30 23:12:16 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"

int	builtin_env(char **args, char ***envp)
{
	int	i;

	i = 0;
	if (args[1])
	{
		printf("env: too many arguments\n");
		return (127);
	}
	while ((*envp)[i])
	{
		printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}
