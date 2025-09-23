/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:12:14 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/23 21:49:58 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"

void	init_command(t_command *cmd)
{
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_delim = NULL;
	cmd->append_mode = 0;
	cmd->redirections = NULL;
	cmd->next = NULL;
}

char	*expand_variables_with_quote(char *str, char **envp, int quote_type)
{
	char	*result;
	size_t	i;
	size_t	start;
	int		in_single;
	int		in_double;
	char	*segment;
	char	*tmp;
	char	*expanded;

	(void)quote_type;
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

void	add_argument(t_command *cmd, char *value, char **envp)
{
	char	*expanded_value;
	char	**new_args;
	int		i;

	expanded_value = expand_variables_with_quote(value, envp, 0);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	new_args = malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
	{
		free(expanded_value);
		free(value);
		return ;
	}
	i = 0;
	while (i < cmd->arg_count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[cmd->arg_count] = expanded_value;
	new_args[cmd->arg_count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->arg_count++;
	free(value);
}

t_command	*build_pipeline(t_pre_token *tokens, char **envp)
{
	t_command	*head;
	t_command	*current;
	t_pre_token	*token;

	head = NULL;
	current = NULL;
	token = tokens;
	while (token)
	{
		if (!current)
		{
			current = malloc(sizeof(t_command));
			if (!current)
				return (NULL);
			init_command(current);
			head = current;
		}
		if (!process_token(&token, &current, &head, envp))
                {
                        ft_free_commands(head);
			return (NULL);
                }
	}
	return (head);
}
