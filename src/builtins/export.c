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
static int	update_env_var(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i] && strcmp(envp[i], var) != 0)
		i++;
	if (!envp[i])
		envp[i + 1] = NULL;
	envp[i] = ft_strdup(var);
	if (!envp[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	process_export_args(char **args, char **envp)
{
	while (*args)
	{
		if (!is_valide_export(*args))
		{
			printf("export: `%s': not a valid identifier\n", *args);
			continue ;
		}
		if (update_env_var(envp, *args) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		args++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(char **args, char **envp)
{
	if (!envp)
		return (EXIT_FAILURE);
	if (!args[1])
	{
		print_export_env(envp);
		return (EXIT_SUCCESS);
	}
	return (process_export_args(args + 1, envp));
}
