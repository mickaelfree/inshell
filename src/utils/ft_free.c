/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:59:24 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/22 18:11:18 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include <libft.h>

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

void	ft_free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->left)
		ft_free_ast(node->left);
	if (node->right)
		ft_free_ast(node->right);
	if (node->token)
		free(node->token);
	free(node);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_commands(t_command *head)
{
	t_command		*current;
	t_command		*next;

	current = head;
	while (current)
	{
		next = current->next;
		free_args_and_redir(current);
		free(current->input_file);
		free(current->output_file);
		free(current->heredoc_delim);
		free(current);
		current = next;
	}
}

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
