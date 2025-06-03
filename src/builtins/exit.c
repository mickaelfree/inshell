/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:21:42 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/02 20:59:14 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

//commentaire abrash 
int is_numeric(char *str)
{
        int i;

        i = 0;
        if (str[i] == '-' || str[i] == '+')
                i++;
        while (str[i])
        {
                if (!ft_isdigit(str[i]))
                        return (0);
                i++;
        }
        return (1);
}
int ft_atoi(char *str)
{
        int i;
        int sign;
        long long result;

        i = 0;
        sign = 1;
        result = 0;
        while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
                i++;
        if (str[i] == '-' || str[i] == '+')
        {
                if (str[i] == '-')
                        sign = -1;
                i++;
        }
        while (str[i] >= '0' && str[i] <= '9')
        {
                result = result * 10 + (str[i] - '0');
                i++;
        }
        if (result > 255)
                return (result % 256);
        return (result * sign);
}
void	builtin_exit(char **args)
{
        if (args[1] && !is_numeric(args[1]))
        {
                printf("exit: %s: numeric argument required\n", args[1]);
                exit(2);
        }
        if (args[1] && args[2])
        {
                printf("exit: too many arguments\n");
        }
        if (!args[1])

            exit(0);
        else
                exit(ft_atoi(args[1]));
}
