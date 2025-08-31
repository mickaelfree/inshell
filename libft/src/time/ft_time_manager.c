/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 04:13:49 by sarunomane        #+#    #+#             */
/*   Updated: 2025/08/30 19:15:39 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "time_manager.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

double	get_proc_uptime(void)
{
	int		fd;
	char	str[201];
	int		len;
	double	time;
	char	*timestr;

	time = 0;
	fd = open("/proc/self/sched", O_RDONLY);
	if (fd < 0)
		return (-1);
	len = read(fd, str, 200);
	close(fd);
	if (len == -1)
		return (-1);
	timestr = ft_strnstr(str, TIME_PARSE, len);
	if (timestr)
	{
		while (!ft_isdigit(*timestr))
			timestr++;
		time = ft_atof((const char *)(timestr)) / 1000;
	}
	return (time);
}

int	get_frames_per_second()
{
	static double	elapsedtime;
	static double	lastrealtime;
	static int		nbr_frames;
	static double	uptime;

	uptime = get_proc_uptime();
	nbr_frames = 0;
	if (!lastrealtime)
		lastrealtime = uptime;
	elapsedtime += uptime - lastrealtime;
	while (elapsedtime < 1.f)
	{
		nbr_frames++;
		if (!lastrealtime)
			lastrealtime = uptime;
		elapsedtime += uptime - lastrealtime;
	}
	return (nbr_frames);
}

double	get_deltatime(void)
{
	double	deltatime;
	int		nbframe;

	nbframe = get_frames_per_second();
	deltatime = (1.0f) / nbframe;
	return (deltatime);
}
