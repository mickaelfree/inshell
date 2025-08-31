/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/30 23:16:20 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

static int	is_valid_identifier(char *name)
{
	if (!name || !*name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

static int	remove_env_var(char ***envp_ptr, char *name)
{
	char	**envp = *envp_ptr;
	char	**new_env;
	int		len = 0;
	int		i = 0;
	int		j = 0;
	size_t	name_len = ft_strlen(name);

	// Compter les variables
	while (envp[len])
		len++;

	new_env = malloc((len + 1) * sizeof(char *));
	if (!new_env)
		return (EXIT_FAILURE);

	// Copier toutes les variables sauf celle à supprimer
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '='))
		{
			new_env[j] = ft_strdup(envp[i]);
			if (!new_env[j])
			{
				while (--j >= 0)
					free(new_env[j]);
				free(new_env);
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free(*envp_ptr);
	*envp_ptr = new_env;
	return (EXIT_SUCCESS);
}

int	builtin_unset(char **args, char ***envp)
{
	int	ret;

	ret = 0;
	if (!args[1])
		return (0);
	args++;
	while (*args)
	{
		if (!is_valid_identifier(*args))
		{
			printf("unset: `%s': not a valid identifier\n", *args);
			ret = 1;
		}
		else
		{
			remove_env_var(envp, *args);
		}
		args++;
	}
	return (ret);
}
