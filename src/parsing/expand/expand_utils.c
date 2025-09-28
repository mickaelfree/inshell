/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:29:00 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/25 16:32:06 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"

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

static char	*ft_parse_name(char *name)
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
	free(rname);
	return (value);
}

char	*trim_leading_spaces(char *result)
{
	char	*start_without_spaces;
	char	*trimmed_result;

	start_without_spaces = result;
	while (*start_without_spaces == ' ' || *start_without_spaces == '\t')
		start_without_spaces++;
	if (start_without_spaces != result)
	{
		trimmed_result = ft_strdup(start_without_spaces);
		free(result);
		return (trimmed_result);
	}
	return (result);
}
