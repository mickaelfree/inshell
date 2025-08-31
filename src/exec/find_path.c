/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 03:33:53 by mickmart          #+#    #+#             */
/*   Updated: 2025/08/18 16:20:24 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static char	*try_absolute_path(char *cmd, int *status)
{
	char	*path;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
		{
			*status = 127;
			return (NULL);
		}
		if (access(cmd, X_OK) == -1)
		{
			*status = 126;
			return (NULL);
		}
		path = ft_strjoin(cmd, "");
		if (!path)
		{
			*status = EXIT_FAILURE;
			return (NULL);
		}
		return (path);
	}
	return (NULL);
}

static char	*try_path_directories(char *cmd, char **paths)
{
	char	*part_path;
	char	*full_path;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			return (NULL);
		full_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	**get_path_directories(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		status;

	status = 0;
	if (!cmd || !env)
		return (NULL);
	path = try_absolute_path(cmd, &status);
	if (!path && status != 0)
	{
		if (status == 127)
			ft_error(" No such file or directory");
		else if (status == 126)
			ft_error(" Permission denied");
		exit(status);
	}
	if (path)
		return (path);
	paths = get_path_directories(env);
	if (!paths)
		return (NULL);
	path = try_path_directories(cmd, paths);
	ft_free(paths);
	return (path);
}
