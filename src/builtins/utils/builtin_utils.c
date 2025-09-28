/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 05:57:02 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 06:32:57 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "libft.h"

static void	init_lookup(t_builtin_entry *builtin_lookup)
{
	builtin_lookup[0] = (t_builtin_entry){"echo", BUILTIN_ECHO};
	builtin_lookup[1] = (t_builtin_entry){"pwd", BUILTIN_PWD};
	builtin_lookup[2] = (t_builtin_entry){"cd", BUILTIN_CD};
	builtin_lookup[3] = (t_builtin_entry){"env", BUILTIN_ENV};
	builtin_lookup[4] = (t_builtin_entry){"export", BUILTIN_EXPORT};
	builtin_lookup[5] = (t_builtin_entry){"unset", BUILTIN_UNSET};
	builtin_lookup[6] = (t_builtin_entry){"exit", BUILTIN_EXIT};
	builtin_lookup[7] = (t_builtin_entry){NULL, BUILTIN_UNKNOWN};
}

t_builtin_type	get_builtin_type(char *cmd)
{
	int				i;
	t_builtin_entry	builtin_lookup[8];

	i = 0;
	init_lookup(builtin_lookup);
	while (builtin_lookup[i].name)
	{
		if (!ft_strncmp((char *)builtin_lookup[i].name, cmd,
				ft_strlen(builtin_lookup[i].name)))
			return (builtin_lookup[i].type);
		i++;
	}
	return (BUILTIN_UNKNOWN);
}
