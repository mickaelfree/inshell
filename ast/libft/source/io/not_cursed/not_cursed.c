/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_cursed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:11 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/24 01:03:03 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "not_cursed/not_cursed.h"
#include "ft_printf/ft_printf.h"

static void	print_divider(t_nc_view *view)
{
	int	i;

	i = 0;
	while (i++ < view->console_width)
		ft_dprintf(view->fd, "━");
	ft_dprintf(view->fd, "\n");
}

static int	count_lines(char *str)
{
	int	lines;
	int	i;

	if (!str)
		return (0);
	i = 0;
	lines = 1;
	while (str[i])
	{
		if (str[i++] == '\n')
			lines++;
	}
	return (lines);
}

t_nc_view	*nc_init(char *info, int width, int height, int fd)
{
	t_nc_view	*view;

	view = (t_nc_view *)malloc(sizeof(t_nc_view));
	if (!view)
		return (NULL);
	view->footer_text = ft_strdup(info);
	if (!view->footer_text)
	{
		nc_free(view);
		return (NULL);
	}
	view->console_width = width;
	view->console_height = height;
	view->footer_displayed = 0;
	view->footer_lines = 1;
	view->fd = fd;
	return (view);
}

void	nc_refresh(t_nc_view *view)
{
	char	*str;

	if (!view || !view->footer_text)
		return ;
	if (view->footer_displayed)
		nc_clear_footer(view);
	view->footer_lines = count_lines(view->footer_text);
	print_divider(view);
	str = view->footer_text;
	ft_dprintf(view->fd, "%s", str);
	if (str[0] && str[ft_strlen(str) - 1] != '\n')
	{
		ft_dprintf(view->fd, "\n");
		view->footer_lines++;
	}
	view->footer_displayed = 1;
}

int	nc_printf(t_nc_view *view, const char *format, ...)
{
	va_list	args;
	int		result;
	int		len;

	if (!view)
		return (FAILURE);
	if (view->footer_displayed)
		nc_clear_footer(view);
	va_start(args, format);
	result = ft_vdprintf(view->fd, format, args);
	va_end(args);
	if (result > 0 && format[0] != '\0')
	{
		len = 0;
		while (format[len])
			len++;
		if (len > 0 && format[len - 1] != '\n')
			ft_dprintf(view->fd, "\n");
	}
	nc_refresh(view);
	return (result);
}
