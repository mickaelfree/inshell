/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_quote_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:52:39 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/04 22:01:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"
#include "libft.h"

static char	*init_clear_quote_state(char *input)
{
	int		len;
	char	*res;

	len = ft_strlen(input);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

static int	process_escape(char *input, char *result, int *i, int *j)
{
	(*i)++;
	if (input[*i])
	{
		result[(*j)++] = input[*i];
		return (1);
	}
	result[(*j)++] = '\\';
	return (0);
}

static int	process_clear_quotes(char *input, char *result, int *inside_double,
		int *inside_single)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (input[++i])
	{
		if (input[i] == '\\')
		{
			if (!process_escape(input, result, &i, &j))
				break ;
		}
		else if (input[i] == '"' && !*inside_single)
			*inside_double = !*inside_double;
		else if (input[i] == '\'' && !*inside_double)
			*inside_single = !*inside_single;
		else
			result[j++] = input[i];
	}
	return (j);
}

void	clear_token_quotes(char **token)
{
	char	*input;
	char	*result;
	int		inside_double;
	int		inside_single;
	int		j;

	input = *token;
	inside_double = 0;
	inside_single = 0;
	result = init_clear_quote_state(input);
	j = process_clear_quotes(input, result, &inside_double, &inside_single);
	result[j] = '\0';
	free(*token);
	*token = result;
}

char	*skip_charset(char *str, char charset)
{
	while (*str == charset)
		str++;
	return (str);
}
