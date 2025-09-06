/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:25:08 by dedme             #+#    #+#             */
/*   Updated: 2025/09/06 20:33:41 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "libft.h"

char	*get_env_value(char *name, char **envp)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

static size_t	calculate_expanded_size(char *str, char **envp)
{
	size_t	final_size;
	int		i;
	int		start;
	char	*var_name;
	char	*value;

	final_size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				// $? peut faire jusqu'à 3 chiffres (255)
				final_size += 3;
				i += 2;
			}
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			{
				start = i + 1;
				while (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
						+ 1] == '_'))
					i++;
				var_name = strndup(str + start, i + 1 - start);
				if (var_name)
				{
					value = get_env_value(var_name, envp);
					if (value)
						final_size += ft_strlen(value);
					free(var_name);
				}
				i++;
			}
			else
			{
				final_size++;
				i++;
			}
		}
		else
		{
			final_size++;
			i++;
		}
	}
	return (final_size);
}

char	*ft_parse_name(char *name)
{
	char	*rname;
	int		j;
	int		i;

	j = 0;
	i = 1;
	rname = malloc(sizeof(char) * (ft_strlen(name)));
	if (!rname)
		return (NULL);
	while (name[i])
		rname[j++] = name[i++];
	rname[j] = '\0';
	return (rname);
}

char	*expand_env(char *name)
{
	char	*value;
	char	*rname;

	rname = ft_parse_name(name);
	value = getenv(rname);
	free(rname); // Ajouter free
	return (value);
}
char	*expand_variables(char *str, char **envp)
{
	int		i;
	int		j;
	char	*status_str;
	int		start;
	char	*var_name;
	char	*value;
	char	*result;
	size_t	final_size;
	size_t	len;
	size_t	value_len;

	if (!str)
		return (NULL);
	final_size = calculate_expanded_size(str, envp);
	result = malloc(final_size + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				// Gestion de $?
				status_str = ft_itoa(g_last_exit_status);
				if (status_str)
				{
					len = ft_strlen(status_str);
					memcpy(result + j, status_str, len);
					j += len;
					free(status_str);
				}
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

                                if (!var_name)
                                {
                                        free(result);
					return (NULL);
                                }
				value = get_env_value(var_name, envp);
				if (value)
				{
					value_len = ft_strlen(value);
					memcpy(result + j, value, value_len);
					j += value_len;
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
