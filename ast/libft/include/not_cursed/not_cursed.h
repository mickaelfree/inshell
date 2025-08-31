/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_cursed.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 06:02:15 by jureix-c          #+#    #+#             */
/*   Updated: 2025/04/24 01:02:27 by jureix-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOT_CURSED_H
# define NOT_CURSED_H

// DEFINES
# define LOG_ESC_CLEAR "\x1b[2J\x1b[H"
# define LOG_ESC_UP_LINE "\x1b[1F"
# define LOG_ESC_CLEAR_LINE "\x1b[2K"

// STRUCTURES
typedef struct s_nc_view
{
	int		console_width;
	int		console_height;
	char	*footer_text;
	int		footer_displayed;
	int		footer_lines;
	int		fd;
}	t_nc_view;

// PROTOTYPES
// Init
t_nc_view	*nc_init(char *info, int width, int height, int fd);
void		nc_free(t_nc_view *view);

// Bas
int			nc_printf(t_nc_view *view, const char *format, ...);
void		nc_clear(t_nc_view *view);
void		nc_update_dimensions(t_nc_view *view, int w, int h);
void		nc_refresh(t_nc_view *view);

// Footer
int			nc_footer(t_nc_view *view, char *info);
int			nc_footerf(t_nc_view *view, const char *format, ...);
void		nc_clear_footer(t_nc_view *view);

#endif
