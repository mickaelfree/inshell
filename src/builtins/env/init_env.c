/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 05:58:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 19:54:13 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_error.h>
#include <ft_strings.h>
#include <ft_utils.h>

#include <stdio.h>
#include <stdlib.h>

char	**init_env(char ***envp)
{
	int		count;
	char	**new_env;
	char	**cur_env;
	int		i;

	cur_env = *envp;
	if (!cur_env)
		return (NULL);
	count = ft_count((void **)cur_env);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (print_error_ret_null(ERR_ALLOC_ENV));
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup((*envp)[i]);
		if (error_alloc(new_env[i], new_env))
			return (NULL);
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}
