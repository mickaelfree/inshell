/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:16 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 18:03:36 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO::
#include "../../includes/inshell.h"

int builtin_pwd(char **args)
{
        char *line;
        (void)args;
        return (0);

        line = getcwd(NULL, 0);
        printf("%s\n", line);
}
