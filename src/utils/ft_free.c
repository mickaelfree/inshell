/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:59:24 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/24 03:41:06 by zsonie           ###   ########lyon.fr   */
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

void	ft_free_commands(t_command *head)
{
	t_command	*current;
	t_command	*next;

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

void	free_token_list(t_pre_token *head)
{
	t_pre_token	*current;
	t_pre_token	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_args_and_redir(t_command *current)
{
	t_redirection	*redir;
	t_redirection	*next_redir;
	int				i;

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
}
