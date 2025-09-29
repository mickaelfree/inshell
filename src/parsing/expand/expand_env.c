/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:25:08 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 20:03:02 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_char.h>
#include <ft_convert.h>
#include <ft_strings.h>
#include <ft_memory.h>

#include <mandatoshell.h>
#include <ft_parsing.h>

#include <stdlib.h>

static int	expand_status_variable(char *result, int *j)
{
	char	*status_str;
	size_t	len;

	status_str = ft_itoa(g_last_exit_status);
	if (status_str)
	{
		len = ft_strlen(status_str);
		ft_memcpy(result + *j, status_str, len);
		*j += len;
		free(status_str);
	}
	return (2);
}

static int	expand_normal_variable(char *str, int i, t_expand_ctx *ctx)
{
	int		start;
	char	*var_name;
	char	*value;
	size_t	value_len;
	int		advance;

	start = i + 1;
	advance = 1;
	while (str[i + advance] && (ft_isalnum(str[i + advance])
			|| str[i + advance] == '_'))
		advance++;
	var_name = ft_strndup(str + start, advance - 1);
	if (!var_name)
		return (-1);
	value = get_env_value(var_name, ctx->envp);
	if (value)
	{
		value_len = ft_strlen(value);
		ft_memcpy(ctx->result + ctx->j, value, value_len);
		ctx->j += value_len;
	}
	free(var_name);
	return (advance);
}

static int	process_dollar_sign(char *str, int i, t_expand_ctx *ctx)
{
	int	advance;

	if (str[i + 1] == '?')
		advance = expand_status_variable(ctx->result, &ctx->j);
	else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
	{
		advance = expand_normal_variable(str, i, ctx);
		if (advance == -1)
			return (-1);
	}
	else
	{
		ctx->result[ctx->j++] = str[i];
		advance = 1;
	}
	return (advance);
}

static char	*process_expansion_loop(char *str, t_expand_ctx *ctx)
{
	int	i;
	int	advance;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			advance = process_dollar_sign(str, i, ctx);
			if (advance == -1)
			{
				free(ctx->result);
				return (NULL);
			}
			i += advance;
		}
		else
			ctx->result[ctx->j++] = str[i++];
	}
	ctx->result[ctx->j] = '\0';
	return (ctx->result);
}

char	*expand_variables(char *str, char **envp)
{
	t_expand_ctx	ctx;
	size_t			final_size;
	char			*result;

	if (!str)
		return (NULL);
	final_size = calculate_expanded_size(str, envp);
	ctx.result = malloc(final_size + 1);
	if (!ctx.result)
		return (NULL);
	ctx.envp = envp;
	ctx.j = 0;
	result = process_expansion_loop(str, &ctx);
	if (!result)
		return (NULL);
	return (trim_leading_spaces(result));
}
