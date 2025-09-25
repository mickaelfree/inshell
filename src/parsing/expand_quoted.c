/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:58:32 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/25 01:59:08 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

char	*expand_variables_with_quote(char *str, char **envp)
{
	char	*result;
	size_t	i;
	size_t	start;
	int		in_single;
	int		in_double;
	char	*segment;
	char	*tmp;
	char	*expanded;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			if (i > start)
			{
				segment = ft_strndup(str + start, i - start);
				if (in_single)
					expanded = ft_strdup(segment);
				else
					expanded = expand_variables(segment, envp);
				tmp = result;
				if (expanded)
				{
					result = ft_strjoin(result, expanded);
					free(expanded);
				}
				else
					result = ft_strjoin(result, segment);
				free(tmp);
				free(segment);
			}
			in_single = !in_single;
			start = i + 1;
			i++;
			continue ;
		}
		if (str[i] == '\"' && !in_single)
		{
			if (i > start)
			{
				segment = ft_strndup(str + start, i - start);
				expanded = expand_variables(segment, envp);
				tmp = result;
				if (expanded)
				{
					result = ft_strjoin(result, expanded);
					free(expanded);
				}
				else
					result = ft_strjoin(result, segment);
				free(tmp);
				free(segment);
			}
			in_double = !in_double;
			start = i + 1;
			i++;
			continue ;
		}
		i++;
	}
	if (start < ft_strlen(str))
	{
		segment = ft_strndup(str + start, ft_strlen(str) - start);
		if (in_single)
			expanded = ft_strdup(segment);
		else
			expanded = expand_variables(segment, envp);
		tmp = result;
		if (expanded)
		{
			result = ft_strjoin(result, expanded);
			free(expanded);
		}
		else
			result = ft_strjoin(result, segment);
		free(tmp);
		free(segment);
	}
	return (result);
}
