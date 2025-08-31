/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:19:09 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/31 04:46:39 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

char	**ft_env(char **envp)
{
	int		count_pointer;
	int		count_char;
	int		total;
	int		i;
	char	**new_env;
	char	*pool_string;

	i = 0;
	count_pointer = 0;
	count_char = 0;
	while (envp[count_pointer])
	{
		count_char += ft_strlen(envp[count_pointer]) + 1;
		count_pointer++;
	}
	total = (sizeof(char *) * (count_pointer + 1)) + (sizeof(char)
			* count_char);
	new_env = malloc(total);
	if (!new_env)
		return (NULL);
	pool_string = (char *)&new_env[count_pointer + 1];
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
/*
int	main(int argc,char **argv,char **envp)
{
		char **new_envp;

		new_envp = ft_env(envp);
		while (*new_envp)
				printf("\n%s\n",*new_envp++);
		printf("\n<===============================>\n");
		while (*envp)
				printf("\n%s\n",*envp++);
		return (0);
}
*/
