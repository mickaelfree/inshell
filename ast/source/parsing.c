/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:45:42 by jureix-c          #+#    #+#             */
/*   Updated: 2025/08/30 00:48:22 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"

char	**realloc_list(char **ptr, size_t newsize)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc((newsize + 1) * sizeof(char *));
	while (ptr[i])
	{
		res[i] = ft_strdup(ptr[i]);
		i++;
	}
	if (!res)
		error_exit();
	if (ptr)
		free_arr(ptr);
	return (res);
}

void	add_elem_to_list(char ***lst, char *string)
{
	int	size;

	size = 0;
	if (*lst == NULL)
	{
		*lst = ft_calloc(2, sizeof(char *));
		**lst = ft_strdup(string);
		*(*lst + 1) = NULL;
		return ;
	}
	while ((*lst)[size])
		size++;
	*lst = realloc_list(*lst, size + 1);
	((*lst)[size]) = ft_strdup(string);
	((*lst)[size + 1]) = NULL;
}

char	*add_token(char ***arr_tokens, char *input, char *start, char *end)
{
	char	*res;

	res = ft_substr(input, start - input, end - start + 1);
	add_elem_to_list(arr_tokens, res);
	free(res);
	return (end + 1);
}

char	*skip_charset(char *str, char charset)
{
	while (*str == charset)
		str++;
	return (str);
}

char	*split_to_tokens(char *input, char ***arr_tokens)
{
	char *start_of_token;
	char *end_of_token;

	start_of_token = input;
	while (*start_of_token != '\0')
	{
		start_of_token = skip_charset(start_of_token, ' ');
		end_of_token = start_of_token;
		while (!ft_strchr("> <|\0", *(start_of_token)))
		{
			if (ft_strchr("\"\'", *end_of_token))
				end_of_token = ft_strchr(end_of_token + 1, *end_of_token);
			if (ft_strchr("> <|\0", *(end_of_token + 1)))
				break ;
			end_of_token++;
		}
		if (ft_strchr("<>", *start_of_token)
			&& *start_of_token == *(start_of_token + 1))
			end_of_token++;
		if (*start_of_token != '\0')
			start_of_token = add_token(arr_tokens, input, start_of_token,
					end_of_token);
	}
	free(input);
	return (NULL);
}