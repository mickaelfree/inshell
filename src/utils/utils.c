/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:59:24 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/02 18:39:16 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
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

void free_ast(t_ast *node)
{
	if (!node)
		return;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->token)
		free(node->token);
	free(node);
}

void clear_token_quotes(char **token)
{
	char	*new_token;
	int		i;
	int		j;

	if (!token || !*token)
		return;
	new_token = ft_calloc(ft_strlen(*token) + 1, sizeof(char));
	if (!new_token)
		return;
	i = 0;
	j = 0;
	while ((*token)[i])
	{
		if ((*token)[i] == '\'' || (*token)[i] == '\"')
			i++;
		else
			new_token[j++] = (*token)[i++];
	}
	new_token[j] = '\0';
	free(*token);
	*token = new_token;
}
