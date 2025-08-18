/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:25:08 by dedme             #+#    #+#             */
/*   Updated: 2025/08/05 00:13:05 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

static char	*get_env_value(char *name, char **envp)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = strlen(name);
	while (envp[i])
	{
		if (strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
char	*ft_parse_name(char *name)
{
	char	*rname;
	int		j;
	int		i;

	j = 0;
	i = 1;
	rname = malloc(sizeof(char) * ft_strlen(name) + 1);
	while (name[i])
		rname[j++] = name[i++];
	//	printf("name = %s\n",rname);
	return (rname);
}

char	*expand_env(char *name)
{
	char	*value;
	char	*rname;

	rname = ft_parse_name(name);
	value = getenv(rname);
	//	printf("value = %s\n", value);
	return (value);
}
char	*expand_variables(char *str, char **envp)
{
	int		i = 0, j;
				char status_str[12];
	int		start;
	char	*var_name;
	char	*value;

	if (!str)
		return (NULL);
	char *result = malloc(strlen(str) * 4 + 1); // Buffer large
	if (!result)
		return (NULL);
	i = 0, j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				// Gestion de $?
				sprintf(status_str, "%d", g_last_exit_status);
				strcpy(result + j, status_str);
				j += strlen(status_str);
				i += 2;
			}
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			{
				// Variable normale $VAR
				start = i + 1;
				while (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
						+ 1] == '_'))
					i++;
				var_name = strndup(str + start, i + 1 - start);
				value = get_env_value(var_name, envp);
				if (value)
				{
					strcpy(result + j, value);
					j += strlen(value);
				}
				free(var_name);
				i++;
			}
			else
			{
				result[j++] = str[i++];
			}
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return (result);
}
