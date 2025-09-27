/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/27 18:11:16 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "error.h"

static int	is_valid_export(char *args)
{
	int		i;
	char	*k_end;

	if (!args || ft_isdigit(*args) || *args == '=')
		return (0);
	k_end = ft_strchr(args, '=');
	if (!k_end)
		k_end = args + ft_strlen(args);
	i = 0;
	while (args + i < k_end)
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	replace_existing_var(char ***envp_ptr, char *var, int index)
{
	char	**envp;
	char	**new_env;
	int		len;
	int		j;

	envp = *envp_ptr;
	len = ft_count((void **)envp);
	new_env = malloc((len + 1) * sizeof(char *));
	if (!new_env)
		return (print_error_ret_err(ERR_ALLOC_EXPORT));
	j = 0;
	while (j < len)
	{
		if (j == index)
			new_env[j] = ft_strdup(var);
		else
			new_env[j] = ft_strdup(envp[j]);
		if (error_alloc(new_env[j], new_env))
			return (print_error_ret_err(ERR_ALLOC_EXPORT));
		j++;
	}
	new_env[len] = NULL;
	ft_free_env(*envp_ptr);
	*envp_ptr = new_env;
	return (EXIT_SUCCESS);
}

static int	add_new_var(char ***envp_ptr, char *var)
{
	char	**envp;
	char	**new_env;
	int		len;
	int		j;

	envp = *envp_ptr;
	len = ft_count((void **)envp);
	new_env = malloc((len + 2) * sizeof(char *));
	if (!new_env)
		return (print_error_ret_err(ERR_ALLOC_EXPORT));
	j = 0;
	while (j < len)
	{
		new_env[j] = ft_strdup(envp[j]);
		if (error_alloc(new_env[j], new_env))
			return (print_error_ret_err(ERR_ALLOC_EXPORT));
		j++;
	}
	new_env[len] = ft_strdup(var);
	if (error_alloc(new_env[len], new_env))
		return (print_error_ret_err(ERR_ALLOC_EXPORT));
	new_env[len + 1] = NULL;
	ft_free_env(*envp_ptr);
	*envp_ptr = new_env;
	return (EXIT_SUCCESS);
}

int	update_env_var(char ***envp_ptr, char *var)
{
	char	**envp;
	char	*key;
	size_t	key_len;
	int		i;

	envp = *envp_ptr;
	key = get_key(var);
	if (!key)
		return (EXIT_FAILURE);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, key_len) && envp[i][key_len] == '=')
		{
			free(key);
			return (replace_existing_var(envp_ptr, var, i));
		}
		i++;
	}
	free(key);
	return (add_new_var(envp_ptr, var));
}

int	builtin_export(t_command *cmd, char **args, char ***envp)
{
	int	i;

	(void)cmd;
	if (!envp)
		return (EXIT_FAILURE);
	g_last_exit_status = 0;
	if (!args[1])
	{
		i = 0;
		while ((*envp)[i])
			printf("export %s\n", (*envp)[i++]);
		return (EXIT_SUCCESS);
	}
	args++;
	while (*args)
	{
		if (!is_valid_export(*args))
			export_error(*args);
		else if (ft_strchr(*args, '=') && update_env_var(envp,
				*args) != EXIT_SUCCESS)
			g_last_exit_status = 1;
		args++;
	}
	return (g_last_exit_status);
}
