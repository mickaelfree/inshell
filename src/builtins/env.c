/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:41 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/05 01:30:51 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "libft.h"

int builtin_env(char *token, char ***envp)
{
    int     i;
    char    **args;
    char    **ev;
    
    ev = *envp;
    if (!ev)
        return (EXIT_FAILURE);
    if (token && *token)
    {
        args = ft_split(token, ' ');
        if (args && args[0])
        {
            printf("env: too many arguments\n");
            ft_free_split(args);
            return (127);
        }
        ft_free_split(args);
    }
    i = 0;
    while (ev[i])
    {
        printf("%s\n", ev[i]);
        i++;
    }
    return (0);
}

char	**init_env(char ***envp)
{
	int		count;
	char	**new_env;
	char	**cur_env;
	int		i;

	cur_env = *envp;
	if (!cur_env)
		return (NULL);
	count = 0;
	while (cur_env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup((*envp)[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}
