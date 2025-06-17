/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/17 19:27:14 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inshell.h"

void	init_builtin(builtin_func *builtin)
{
	builtin[BUILTIN_ECHO] = builtin_echo;
	builtin[BUILTIN_PWD] = builtin_pwd;
	builtin[BUILTIN_CD] = builtin_cd;
	builtin[BUILTIN_ENV] = builtin_env;
	builtin[BUILTIN_EXPORT] = builtin_export;
	builtin[BUILTIN_UNSET] = builtin_unset;
	builtin[BUILTIN_EXIT] = builtin_exit;
}
void	init_lookup(t_builtin_entry *builtin_lookup)
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

t_builtin_type	get_builtin_type(const char *cmd)
{
	int				i;
	t_builtin_entry	builtin_lookup[7];

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
int	is_builtin(char **args, char **envp)
{
	t_builtin_type	type;
	builtin_func	builtin_functions[7];



        init_builtin(builtin_functions);
	type = get_builtin_type(args[0]);
	if (type == BUILTIN_UNKNOWN)
		return (0);
	return (builtin_functions[type](args, envp));
}
// int	is_builtin(char **args, char **envp)
// {
// 	if (!strcmp(args[0], "echo"))
// 	{
// 		builtin_echo(args);
// 		return (1);
// 	}
// 	if (!strcmp(args[0], "pwd"))
// 	{
// 		builtin_pwd();
// 		return (1);
// 	}
// 	if (!strcmp(args[0], "cd"))
// 	{
// 		builtin_cd(args, envp);
// 		return (1);
// 	}
// 	if (!strcmp(args[0], "env"))
// 	{
// 		builtin_env(args, envp);
// 		return (1);
// 	}
// 	if (!strcmp(args[0], "export"))
// 	{
// 		builtin_export(args, envp);
// 		return (1);
// 	}
// 	if (!strcmp(args[0], "unset"))
// 	{
// 		builtin_unset(args, envp);
// 		return (1);
// 	}
// 	if (!strcmp(args[0], "exit"))
// 	{
// 		builtin_exit(args);
// 		return (1);
// 	}
// 	if (!strcmp(args[0], ">>"))
// 	{
// 		builtin_exit(args);
// 		return (1);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	char	**new_env;

	// TODO: recuper les envp
	new_env = ft_env(envp);
	while (1)
	{
		line = readline("Inshell>");
		if (!line)
			break ;
		add_history(line);
		pre_token(line);
		args = ft_split(line, ' ');
		if (!is_builtin(args, new_env))
			execute_cmd(args, new_env);
		// printf("args: %s\n", args[0]);
		// printf("args: %s\n", args[1]);
		// exec(line);
		free(line);
	}
	return (0);
}
