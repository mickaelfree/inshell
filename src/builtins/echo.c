/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 17:44:34 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO::
#include "../../includes/inshell.h"
#include <stdlib.h>

int	builtin_echo(char **args)
{
        int flag;

       flag= 0; 
        if (!args[1] )
        {
                write(1, "\n", 1);
                return (EXIT_SUCCESS);
        }
        args++;
        while (*args)
        {
                if (!strncmp(*args, "-n", 2))
                {
                        flag = 1;
                        args++;
                        continue;
                }
                write(1, *args, strlen(*args));
                if (*(args + 1))
                        write(1, " ", 1);
                args++;
        }
       if (!flag) 
                write(1, "\n", 1);
        return (EXIT_SUCCESS);
}
