/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:58:32 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/29 20:03:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strings.h>

#include <ft_structs.h>
#include <ft_parsing.h>

#include <stdlib.h>

static void	init_quote_ctx(t_quote_ctx *ctx, char *str, char **envp)
{
	ctx->str = str;
	ctx->result = ft_strdup("");
	ctx->envp = envp;
	ctx->i = 0;
	ctx->start = 0;
	ctx->in_single = 0;
	ctx->in_double = 0;
}

static void	process_segment(t_quote_ctx *ctx, int expand_vars)
{
	char	*segment;
	char	*expanded;
	char	*tmp;

	if (ctx->i <= ctx->start)
		return ;
	segment = ft_strndup(ctx->str + ctx->start, ctx->i - ctx->start);
	if (expand_vars)
		expanded = expand_variables(segment, ctx->envp);
	else
		expanded = ft_strdup(segment);
	tmp = ctx->result;
	if (expanded)
	{
		ctx->result = ft_strjoin(ctx->result, expanded);
		free(expanded);
	}
	else
		ctx->result = ft_strjoin(ctx->result, segment);
	free(tmp);
	free(segment);
}

static void	toggle_quote_state(t_quote_ctx *ctx, char quote_char)
{
	process_segment(ctx, (quote_char == '\'' && !ctx->in_single)
		|| (quote_char == '"') || (!ctx->in_single && !ctx->in_double));
	if (quote_char == '\'')
		ctx->in_single = !ctx->in_single;
	else
		ctx->in_double = !ctx->in_double;
	ctx->start = ctx->i + 1;
	ctx->i++;
}

static void	process_final_segment(t_quote_ctx *ctx)
{
	if (ctx->start < ft_strlen(ctx->str))
	{
		ctx->i = ft_strlen(ctx->str);
		process_segment(ctx, !ctx->in_single);
	}
}

char	*expand_variables_with_quote(char *str, char **envp)
{
	t_quote_ctx	ctx;

	if (!str)
		return (NULL);
	init_quote_ctx(&ctx, str, envp);
	if (!ctx.result)
		return (NULL);
	while (ctx.str[ctx.i])
	{
		if (ctx.str[ctx.i] == '\'' && !ctx.in_double)
			toggle_quote_state(&ctx, '\'');
		else if (ctx.str[ctx.i] == '"' && !ctx.in_single)
			toggle_quote_state(&ctx, '"');
		else
			ctx.i++;
	}
	process_final_segment(&ctx);
	return (ctx.result);
}
