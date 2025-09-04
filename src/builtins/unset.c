/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 20:28:52 by zsonie           ###   ########lyon.fr   */
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
	free_env(*envp_ptr);
	*envp_ptr = new_env;
	return (EXIT_SUCCESS);
}

int builtin_unset(char *token, char ***envp)
{
    char **args;
    char **original_args;
    int ret;
    int i;

    if (!token)
        return (EXIT_FAILURE);
    args = ft_split(token, ' ');
    if (!args)
        return (EXIT_FAILURE);
    if (!args[0])
    {
        ft_free_split(args);
        return (EXIT_FAILURE);
    }
    original_args = args; // Save original pointer for freeing
    ret = EXIT_SUCCESS;
    i = 0;
    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            printf("unset: `%s': not a valid identifier\n", args[i]);
            ret = EXIT_FAILURE;
        }
        else
            remove_env_var(envp, args[i]);
        i++;
    }
    ft_free_split(original_args);
    return (ret);
}
