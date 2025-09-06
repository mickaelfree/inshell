/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:49:57 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 22:01:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

// static void	init_builtin(builtin_func *builtin)
// {
// 	builtin[BUILTIN_ECHO] = builtin_echo;
// 	builtin[BUILTIN_PWD] = builtin_pwd;
// 	builtin[BUILTIN_CD] = builtin_cd;
// 	builtin[BUILTIN_ENV] = builtin_env;
// 	builtin[BUILTIN_EXPORT] = builtin_export;
// 	builtin[BUILTIN_UNSET] = builtin_unset;
// 	builtin[BUILTIN_EXIT] = builtin_exit;
// }

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

static t_builtin_type	get_builtin_type(const char *cmd)
{
	int				i;
	t_builtin_entry	builtin_lookup[8];

	i = 0;
	init_lookup(builtin_lookup);
	while (builtin_lookup[i].name)
	{
		if (!strcmp(builtin_lookup[i].name, cmd))
			return (builtin_lookup[i].type);
		i++;
	}
	return (BUILTIN_UNKNOWN);
}
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

int	execute_builtin(char **args, char ***envp)
{
	t_builtin_type	type;

	(void)envp;
	if (!args || !args[0])
		return (-1);
	type = get_builtin_type(args[0]);
        if (type == BUILTIN_UNKNOWN)
                type = -1;
	return ((int)type);
}

int	execute_builtin(char **args, char ***envp)
{
	t_builtin_type	type;
	builtin_func	builtin_functions[7];

	// init_builtin(builtin_functions);
	type = get_builtin_type(args[0]);
	if (type == BUILTIN_UNKNOWN)
		return (-1);
	return (builtin_functions[type](args, envp));
}
