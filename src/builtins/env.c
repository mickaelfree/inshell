/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:41 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/27 14:07:54 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

int	builtin_env(char **args, char **envp)
{
	int	i;

	i = 0;
	if (args[1])
        {
                printf("env: too many arguments\n");
                return (1);
        }
	while (envp[i])
        {
		printf("%s\n", envp[i]);
		i++;
        }
	return (0);
}
