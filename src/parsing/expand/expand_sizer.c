/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_sizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:32:06 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 20:04:45 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_char.h>
#include <ft_convert.h>
#include <ft_strings.h>

#include <mandatoshell.h>
#include <ft_parsing.h>

#include <stdlib.h>

static size_t	handle_status_var(int *i)
{
	char	*status_str;
	size_t	size;

	status_str = ft_itoa(g_last_exit_status);
	if (status_str)
	{
		size = ft_strlen(status_str);
		free(status_str);
		*i += 2;
		return (size);
	}
	*i += 2;
	return (0);
}

static size_t	handle_normal_var(char *str, int *i, char **envp)
{
	int		start;
	char	*var_name;
	char	*value;
	size_t	size;

	start = *i + 1;
	while (str[*i + 1] && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_'))
		(*i)++;
	var_name = ft_strndup(str + start, *i + 1 - start);
	size = 0;
	if (var_name)
	{
		value = get_env_value(var_name, envp);
		if (value)
			size = ft_strlen(value);
		free(var_name);
	}
	(*i)++;
	return (size);
}

static size_t	process_dollar_variable(char *str, int *i, char **envp)
{
	if (str[*i + 1] == '?')
		return (handle_status_var(i));
	else if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_')
		return (handle_normal_var(str, i, envp));
	else
	{
		(*i)++;
		return (1);
	}
}

size_t	calculate_expanded_size(char *str, char **envp)
{
	size_t	final_size;
	int		i;

	final_size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			final_size += process_dollar_variable(str, &i, envp);
		else
		{
			final_size++;
			i++;
		}
	}
	return (final_size);
}
