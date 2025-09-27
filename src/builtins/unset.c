/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/27 23:53:29 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "utils.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

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

static int	rm_var(char **envp, char **new_env, char *name)
{
	int		i;
	int		j;
	size_t	name_len;

	name_len = ft_strlen(name);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], name, name_len) == 0
				&& envp[i][name_len] == '='))
		{
			new_env[j] = ft_strdup(envp[i]);
			if (error_alloc(new_env[j], new_env))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (EXIT_SUCCESS);
}

static int	remove_env_var(char ***envp_ptr, char *name)
{
	char	**envp;
	char	**new_env;

	envp = *envp_ptr;
	new_env = malloc((ft_count((void **)envp) + 1) * sizeof(char *));
	if (!new_env)
		return (print_error_ret_err(ERR_ALLOC_UNSET));
	if (rm_var(envp, new_env, name) != EXIT_SUCCESS)
	{
		ft_free_env(new_env);
		return (EXIT_FAILURE);
	}
	ft_free_env(*envp_ptr);
	*envp_ptr = new_env;
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_command *cmd, char **args, char ***envp)
{
	int	ret;

	(void)cmd;
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
