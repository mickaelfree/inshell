/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:16 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 18:20:15 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO::
#include "../../includes/inshell.h"

int builtin_pwd(void)
{
        char *line = NULL;

        line = getcwd(line, 0);
        if (!line)
                return (EXIT_FAILURE);
        printf("%s\n", line);
        free(line);
        return (EXIT_SUCCESS);
}
