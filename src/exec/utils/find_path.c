/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 03:33:53 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 19:59:47 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_structs.h"
#include <ft_strings.h>
#include <ft_utils.h>
#include <mandatoshell.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

static char	*try_current_directory(char *cmd)
{
	char	*path;

	path = ft_strjoin("./", cmd);
	if (path && access(path, F_OK | X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*find_path(char *cmd, char **env, t_child_ctx ctx)
{
	char	**paths;
	char	*path;
	int		status;

	status = 0;
	if (!cmd || !env)
		return (NULL);
	path = try_absolute_path(cmd, &status);
	if (!path && status != 0)
		handle_error_ctx(NULL, status, ctx);
	if (path)
		return (path);
	paths = get_path_directories(env);
	if (!paths)
		return (try_current_directory(cmd));
	path = try_path_directories(cmd, paths);
	ft_free(paths);
	return (path);
}
