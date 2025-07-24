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
#include <stddef.h>

int	is_valide_export(char *args)
{
	int	i;
	char	*key_end;

	if (!args || ft_isdigit(*args))
		return (0);
	key_end = strchr(args, '=');
	if (!key_end)
		key_end = args + ft_strlen(args);
	i = 0;
	while (args + i < key_end)
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
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
static char *get_key(char *var)
{
	char	*key_end;

	key_end = strchr(var, '=');
	if (!key_end)
		return (ft_strdup(var));
	return (strndup(var, key_end - var));
}
static int tab_len(char **tab)
{
        int i;

        i = 0;
        while (tab[i])
                i++;
        return (i);
}

static int	update_env_var(char ***envp_ptr, char *var)
{
	char **envp = *envp_ptr;
	char *key = get_key(var);
	int i = 0;
	size_t key_len;

	if (!key)
		return (EXIT_FAILURE);
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (!strncmp(envp[i], key, key_len) && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(var);
			free(key);
			if (!envp[i])
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	int len = tab_len(envp);
	char **new_env = calloc(len + 2, sizeof(char *));
	if (!new_env)
	{
		free(key);
		return (EXIT_FAILURE);
	}
        int j = 0;
        while(j<len)
        {
		new_env[j] = envp[j];
                j++;
        }
	new_env[len] = ft_strdup(var);
	if (!new_env[len])
	{
		free(new_env);
		free(key);
		return (EXIT_FAILURE);
	}
	new_env[len + 1] = NULL;
	free(envp); 
	*envp_ptr = new_env;
	free(key);
	return (EXIT_SUCCESS);
}

static int	process_export_args(char **args, char ***envp)
{
	while (*args)
	{
		if (!is_valide_export(*args))
		{
			printf("export: `%s': not a valid identifier\n", *args);
                        args++;
			continue ;
		}
		if (update_env_var(envp, *args) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		args++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(char **args, char ***envp)
{
	if (!envp)
		return (EXIT_FAILURE);
	if (!args[1])
	{
		print_export_env(*envp);
		return (EXIT_SUCCESS);
	}
	return (process_export_args(args + 1, envp));
}
