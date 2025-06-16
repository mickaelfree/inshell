/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:30:44 by mickmart          #+#    #+#             */
/*   Updated: 2025/06/15 18:24:13 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/inshell.h"

static const builtin_func_t builtin_functions[] = {
    [BUILTIN_ECHO]   = builtin_echo,    // Index 0 → adresse de builtin_echo
    [BUILTIN_PWD]    = builtin_pwd,     // Index 1 → adresse de builtin_pwd  
    [BUILTIN_CD]     = builtin_cd,      // Index 2 → adresse de builtin_cd
    [BUILTIN_ENV]    = builtin_env,     // Index 3 → adresse de builtin_env
    [BUILTIN_EXPORT] = builtin_export,  // Index 4 → adresse de builtin_export
    [BUILTIN_UNSET]  = builtin_unset,   // Index 5 → adresse de builtin_unset
    [BUILTIN_EXIT]   = builtin_exit     // Index 6 → adresse de builtin_exit
};
static const t_builtin_entry builtin_lookup[] = {
    {"echo",   BUILTIN_ECHO},
    {"pwd",    BUILTIN_PWD},
    {"cd",     BUILTIN_CD},
    {"env",    BUILTIN_ENV},
    {"export", BUILTIN_EXPORT},
    {"unset",  BUILTIN_UNSET},
    {"exit",   BUILTIN_EXIT},
    {NULL,     BUILTIN_UNKNOWN}
};

t_builtin_type get_builtin_type(const char *cmd)
{
    for (int i = 0; builtin_lookup[i].name; i++) {
        if (!strcmp(builtin_lookup[i].name, cmd))
            return builtin_lookup[i].type;
    }
    return BUILTIN_UNKNOWN;
}
//int is_execute_builtin(char **args, char **envp)
int	is_builtin(char **args, char **envp)
{
    // Étape 1: String → Enum (O(n) unavoidable pour la recherche)
    t_builtin_type type = get_builtin_type(args[0]);
    
    if (type == BUILTIN_UNKNOWN)
        return 0;  // Pas un builtin
        
    // Étape 2: Enum → Function Call (O(1) pur !)
    return builtin_functions[type](args, envp);
    //     ^^^^^^^^^^^^^^^^^^^^^^^
    //     Jump direct via array indexing !
}
//int	is_builtin(char **args, char **envp)
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
        char    **new_env;

        
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
		if(!is_builtin(args, new_env))
                        execute_cmd(args, new_env);
		//printf("args: %s\n", args[0]);
		//printf("args: %s\n", args[1]);
		// exec(line);
		free(line);
	}
	return (0);
}
