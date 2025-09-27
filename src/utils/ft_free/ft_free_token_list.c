/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:51:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 00:51:40 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include<ft_structs.h>
#include<stdlib.h>

void	ft_free_token_list(t_pre_token *head)
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
