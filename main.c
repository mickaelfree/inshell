/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/23 22:18:34 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/inshell.h"

int	main(void)
{
        //TODO:
	char	*line;

	while (1)
	{
                line = readline("");
		if (!line)
			break ;
		add_history(line);
                //TODO:
                //ajouter la logique de parsing
		printf("%s", line);
                //exec(line);
		free(line);
	}
	return (0);
}
