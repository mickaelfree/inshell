/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   footer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:58:22 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/24 01:00:06 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "not_cursed/not_cursed.h"
#include "ft_printf/ft_printf.h"

int	nc_footer(t_nc_view *view, char *new)
{
	if (view->footer_text)
		free(view->footer_text);
	view->footer_text = ft_strdup(new);
	if (!view->footer_text)
	{
		nc_free(view);
		return (FAILURE);
	}
	nc_refresh(view);
	return (SUCCESS);
}

int	nc_footerf(t_nc_view *view, const char *format, ...)
{
	va_list	args;

	if (view->footer_text)
		free(view->footer_text);
	view->footer_text = ft_calloc(view->console_width + 1, sizeof(char));
	if (!view->footer_text)
	{
		nc_free(view);
		return (FAILURE);
	}
	va_start(args, format);
	ft_vsnprintf(view->footer_text, view->console_width + 1, \
		format, args);
	va_end(args);
	if (!view->footer_text)
	{
		nc_free(view);
		return (FAILURE);
	}
	nc_refresh(view);
	return (SUCCESS);
}

void	nc_clear_footer(t_nc_view *view)
{
	int	lines_to_clear;
	int	i;

	if (!view || !view->footer_displayed)
		return ;
	lines_to_clear = view->footer_lines + 1;
	ft_dprintf(view->fd, "\r");
	i = 0;
	while (i++ < lines_to_clear)
		ft_dprintf(view->fd, "\x1b[2K\x1b[1A");
	ft_dprintf(view->fd, "\x1b[1B");
	view->footer_displayed = 0;
}
