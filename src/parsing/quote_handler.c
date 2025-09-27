/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:52:39 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/27 23:40:18 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mandatoshell.h"
#include "is_char.h"
#include "utils.h"

static void	handle_quote_char(char c, int *in_single, int *in_double,
		char **write_ptr)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
	else
		*(*write_ptr)++ = c;
}

char	*remove_quotes(char *token, int len)
{
	char	*result;
	char	*write_ptr;
	int		i;
	int		in_single;
	int		in_double;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	write_ptr = result;
	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < len)
	{
		handle_quote_char(token[i], &in_single, &in_double, &write_ptr);
		i++;
	}
	*write_ptr = '\0';
	return (result);
}

static int	quote_state_check(int quote_state, t_pre_token **head)
{
	if (quote_state > 0)
	{
		printf("Error: unclosed quote\n");
		free_token_list(*head);
		*head = NULL;
		return (0);
	}
	return (1);
}

static void	quote_state_update(char **ptr, int *quote_state, char *quote_char)
{
	*quote_char = *(*ptr);
	if (*quote_char == '\'')
		*quote_state = 1;
	else if (*quote_char == '"')
		*quote_state = 2;
	(*ptr)++;
}

int	check_for_quotes(t_pre_token **head, char **ptr)
{
	int		quote_state;
	char	quote_char;

	quote_state = 0;
	while (*(*ptr))
	{
		if (quote_state == 0 && (is_whitespace(*(*ptr))
				|| is_operator(*(*ptr))))
			break ;
		if (quote_state == 0 && is_quote(*(*ptr)))
		{
			quote_state_update(ptr, &quote_state, &quote_char);
			continue ;
		}
		if (quote_state > 0 && *(*ptr) == quote_char)
		{
			quote_state = 0;
			(*ptr)++;
			continue ;
		}
		(*ptr)++;
	}
	if (!quote_state_check(quote_state, head))
		return (0);
	return (1);
}
