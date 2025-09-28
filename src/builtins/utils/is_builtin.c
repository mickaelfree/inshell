/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:49:57 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 06:32:57 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

int	is_builtin(char **args)
{
	t_builtin_type	type;

	if (!args || !args[0])
		return (-1);
	type = get_builtin_type(args[0]);
	if (type == BUILTIN_UNKNOWN)
		type = -1;
	return ((int)type);
}
