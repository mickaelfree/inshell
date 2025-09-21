/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:35:03 by sarunomane        #+#    #+#             */
/*   Updated: 2025/09/21 18:43:12 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_MANAGER_H
# define TIME_MANAGER_H

# define TIME_PARSE "se.exec_start"

/** @name GET_PROC_UPTIME
** @brief Get the CPU runtime in seconds.
**
** @return CPU runtime
*/
double	get_proc_uptime(void);
//////////////////////////////////////////////////////////

/** @name GET_FRAMES_PER_SECOND
** @brief Get how many frames are in one second.
**
** @return frames/second
*/
int		get_frames_per_second(void);
//////////////////////////////////////////////////////////

/** @name GET_DELTATIME
** @brief Get a specific deltatime(1s/nbframes).
**
** @return deltatime
*/
double	get_deltatime(void);
//////////////////////////////////////////////////////////

#endif