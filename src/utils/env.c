/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:19:09 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/31 18:58:29 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

static int calculate_size(char **envp, int *count_pointer)
{
	int	count_char;

	count_char = 0;
	// printf("count_pointer addr: %p, %d\n", count_pointer, *count_pointer);
	while (envp[*count_pointer])
	{
		count_char += ft_strlen(envp[*count_pointer]) + 1;
		(*count_pointer)++;
	}
	return ((sizeof(char *) * (*count_pointer + 1)) + (sizeof(char)
			* count_char));
}

char	**ft_env(char **envp)
{
	int		total;
	int		i;
	int		count_pointer;
	char	**new_env;
	char	*pool_string;

	count_pointer = 0;
	total = calculate_size(envp, &count_pointer);
	new_env = malloc(total);
	if (!new_env)
		return (NULL);
	pool_string = (char *)&new_env[count_pointer + 1];
	i = 0;
	while (i < count_pointer)
	{
		new_env[i] = pool_string;
		total = ft_strlen(envp[i]) + 1;
		memcpy(pool_string, envp[i], total);
		i++;
		pool_string += total;
	}
	new_env[count_pointer] = NULL;
	return (new_env);
}
