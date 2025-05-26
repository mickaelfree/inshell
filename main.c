/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 17:11:42 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/inshell.h"

int	main(void)
{
	char	*line;
	char	**args;

	// TODO:
	while (1)
	{
		line = readline("Inshell>");
		if (!line)
			break ;
		add_history(line);
		//printf(" %s\n", line);
		args = ft_split(line, ' ');
		if (!strcmp(args[0], "echo"))
			builtin_echo(args);
		printf("args: %s\n", args[0]);
		printf("args: %s\n", args[1]);
		// exec(line);
		free(line);
	}
	return (0);
}
