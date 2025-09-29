/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:41 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 19:53:36 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_structs.h>
#include <ft_strings.h>
#include <stdio.h>

int	builtin_env(t_command *cmd, char **args, char ***envp)
{
	int	i;

	(void)cmd;
	i = 0;
	if (args[1])
	{
		printf("env: too many arguments\n");
		return (127);
	}
	while ((*envp)[i])
	{
		if (ft_strchr((*envp)[i], '='))
			printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}
