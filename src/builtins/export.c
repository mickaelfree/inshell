/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/23 14:40:29 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/inshell.h"

int	is_valide_export(char *args)
{
	int		i;
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
static char	*get_key(char *var)
{
	char	*key_end;

	key_end = strchr(var, '=');
	if (!key_end)
		return (ft_strdup(var));
	return (strndup(var, key_end - var));
}
static int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	update_env_var(char ***envp_ptr, char *var)
{
	char	**envp;
	char	*key;
	int		i;
	size_t	key_len;
	int		len;
	char	**new_env;
	int		j;

	envp = *envp_ptr;
	key = get_key(var);
	if (!key)
		return (EXIT_FAILURE);
	key_len = ft_strlen(key);
	
	// Chercher si la variable existe déjà
	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], key, key_len) && envp[i][key_len] == '=')
		{
			// Variable existe, remplacer tout l'environnement
			len = tab_len(envp);
			new_env = malloc((len + 1) * sizeof(char *));
			if (!new_env)
			{
				free(key);
				return (EXIT_FAILURE);
			}
			j = 0;
			while (j < len)
			{
				if (j == i)
					new_env[j] = ft_strdup(var);
				else
					new_env[j] = ft_strdup(envp[j]);
				if (!new_env[j])
				{
					while (--j >= 0)
						free(new_env[j]);
					free(new_env);
					free(key);
					return (EXIT_FAILURE);
				}
				j++;
			}
			new_env[len] = NULL;
			free_env(*envp_ptr);  // Libérer l'ancien bloc entier
			*envp_ptr = new_env;
			free(key);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	
	// Variable n'existe pas, l'ajouter
	len = tab_len(envp);
	new_env = malloc((len + 2) * sizeof(char *));
	if (!new_env)
	{
		free(key);
		return (EXIT_FAILURE);
	}
	j = 0;
	while (j < len)
	{
		new_env[j] = ft_strdup(envp[j]);
		if (!new_env[j])
		{
			while (--j >= 0)
				free(new_env[j]);
			free(new_env);
			free(key);
			return (EXIT_FAILURE);
		}
		j++;
	}
	new_env[len] = ft_strdup(var);
	if (!new_env[len])
	{
		while (--j >= 0)
			free(new_env[j]);
		free(new_env);
		free(key);
		return (EXIT_FAILURE);
	}
	new_env[len + 1] = NULL;
	
	free(*envp_ptr);  // Libérer l'ancien bloc entier
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
		if (strchr(*args, '='))
		{
			if (update_env_var(envp, *args) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
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
