/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/27 16:38:52 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// TODO::
#include "../../includes/inshell.h"

static int is_valid_identifier(char *name)
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

static void delete_var(char **envp, char *arg, int i)
{
	size_t len;

	len = strlen(arg);
	if (strncmp(envp[i], arg, len) == 0 && envp[i][len] == '=')
	{
		free(envp[i]);
		while (envp[i])
		{
			envp[i] = envp[i + 1];
			i++;
		}
	}
}

int builtin_unset(char **args, char **envp)
{
	int ret;
	int i;

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
			i = 0;
			while (envp[i])
			{
				delete_var(envp, *args, i);
				if (!envp[i])
					break ;
				i++;
			}
		}
		args++;
	}
	return (ret);
}
