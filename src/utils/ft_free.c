/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:59:24 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/05 01:13:59 by zsonie           ###   ########lyon.fr   */
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
	t_redirection	*redir;
	t_redirection	*next_redir;
	int				i;

	current = head;
	while (current)
	{
		next = current->next;
		
		if (current->args)
		{
			i = 0;
			while (i < current->arg_count)
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		
		redir = current->redirections;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->filename);
			free(redir);
			redir = next_redir;
		}
		
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
