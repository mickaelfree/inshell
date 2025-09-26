/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:35:38 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/25 17:03:31 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mandatoshell.h"

unsigned int	ft_count(void **ptrs)
{
	int	count;

	if (!ptrs)
		return (0);
	count = 0;
	while (ptrs[count])
		count++;
	return (count);
}

void	ft_free_tab(void **ptrs)
{
	int	i;

	if (!ptrs)
		return ;
	i = 0;
	while (ptrs[i])
	{
		free(ptrs[i]);
		i++;
	}
	free(ptrs);
}

void	ft_free_ctx(t_quote_ctx *ctx)
{
	if (ctx->str)
		free(ctx->str);
	if (ctx->result)
		free(ctx->result);
	if (ctx->envp)
		ft_free_env(ctx->envp);
	free(ctx);
}

int	error_alloc(char *ptr, char **ptrs)
{
	if (!ptr)
	{
		if (ptrs)
			ft_free_tab((void **)ptrs);
		return (1);
	}
	return (0);
}
