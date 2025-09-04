/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:41 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 02:06:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

static void ft_free_split(char **split)
{
    int i;

    if (!split)
        return;
    
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

int	builtin_env(char *token, char ***envp)
{
	int		i;
	char	**args;

	i = 0;
	if (token)
	{
		args = ft_split(token, ' ');
		if (args[0])
		{
			printf("env: too many arguments\n");
			ft_free_split(args);
			return (127);
		}
		ft_free_split(args);
	}
    while (envp && (*envp)[i])
    {
        printf("%s\n", (*envp)[i]);
        i++;
    }
    return (0);
}
