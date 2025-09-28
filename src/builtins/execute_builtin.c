/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 05:59:50 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 06:32:57 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include "libft.h"

static void	init_builtin(t_builtin_func *builtin)
{
	builtin[BUILTIN_ECHO] = builtin_echo;
	builtin[BUILTIN_PWD] = builtin_pwd;
	builtin[BUILTIN_CD] = builtin_cd;
	builtin[BUILTIN_ENV] = builtin_env;
	builtin[BUILTIN_EXPORT] = builtin_export;
	builtin[BUILTIN_UNSET] = builtin_unset;
	builtin[BUILTIN_EXIT] = builtin_exit;
}

int	execute_builtin(t_command *cmd, char ***envp)
{
	t_builtin_type	type;
	t_builtin_func	t_builtin_functions[7];

	init_builtin(t_builtin_functions);
	type = get_builtin_type(cmd->args[0]);
	if (type == BUILTIN_UNKNOWN)
		return (-1);
	return (t_builtin_functions[type](cmd, cmd->args, envp));
}
