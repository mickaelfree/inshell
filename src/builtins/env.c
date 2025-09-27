/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:41 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/27 17:39:08 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "error.h"

char	**init_env(char ***envp)
{
	int		count;
	char	**new_env;
	char	**cur_env;
	int		i;

	cur_env = *envp;
	if (!cur_env)
		return (NULL);
	count = ft_count((void **)cur_env);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (print_error_ret_NULL(ERR_ALLOC_ENV));
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup((*envp)[i]);
		if (error_alloc(new_env[i], new_env))
			return (NULL);
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

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
		printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}
