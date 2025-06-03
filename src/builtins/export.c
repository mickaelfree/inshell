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

int	is_valide_export(char *args)
{
	int	i;
	int	is_valid;

	if (!args || ft_isdigit(args[0]))
		return (0);
	i = 0;
	while (args[i])
	{
		is_valid = ((ft_isalnum(args[i]) || args[i] == '_'));
		if (!is_valid)
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_env(char **envp)
{
	while (*envp)
		printf("export %s\n", *envp++);
}

int	builtin_export(char **args, char **envp)
{
	int	i;
	int	found;

	if (!args[1])
	{
		print_export_env(envp);
		return (EXIT_SUCCESS);
	}
	args++;
	while (*args)
	{
		if (!is_valide_export(*args))
		{
			printf("export: `%s':not a valid identifier\n", *args);
			args++;
			continue ;
		}
		i = 0;
		found = 0;
		while (envp[i])
		{
			found = !strcmp(envp[i], *args);
			if (found)
			{
				free(envp[i]);
				envp[i] = ft_strdup(*args);
				break ;
			}
			i++;
		}
		if (!found && !envp[i])
		{
			envp[i] = ft_strdup(*args);
			envp[i + 1] = NULL;
		}
		args++;
	}
	return (EXIT_SUCCESS);
}
