/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:11 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/24 01:00:27 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "not_cursed/not_cursed.h"
#include "ft_printf/ft_printf.h"

void	nc_clear(t_nc_view *view)
{
	ft_dprintf(view->fd, "\x1b[2J\x1b[H");
	view->footer_displayed = 0;
}

void	nc_update_dimensions(t_nc_view *view, int w, int h)
{
	view->console_width = w;
	view->console_height = h;
}

void	nc_free(t_nc_view *view)
{
	if (view->footer_text)
		free(view->footer_text);
	free(view);
}
