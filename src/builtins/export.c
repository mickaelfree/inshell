/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/27 17:11:13 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// TODO::
#include "../../includes/inshell.h"

int	is_valide_export(char **args)
{
	int	i;

	i = 0;
        if (ft_isdigit(args[0][i++]))
		return (EXIT_FAILURE);
	while (args[0][i])
	{
		if (!ft_isalnum(args[0][i]) && args[0][i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
int	is_args(char **args, char **envp)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		while (envp[i])
		{
			printf("export %s\n", envp[i]);
			i++;
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(char **args, char **envp)
{
	int	i;

	if (is_args(args, envp) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	args++;
	while (*args)
	{
		i = 1;
		if (is_valide_export(args)==EXIT_FAILURE)
		{
			printf("export: `%s':not a valid identifier\n", *args);
			return (EXIT_SUCCESS);
		}
		while (envp[i])
		{
			if (!strcmp(envp[i], *args))
			{
				free(envp[i]);
				envp[i] = ft_strdup(*args);
				return (EXIT_SUCCESS);
			}
			i++;
		}
		envp[i] = ft_strdup(*args);
		envp[i + 1] = NULL;
		args++;
	}
	return (EXIT_SUCCESS);
}
