/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:18:21 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/27 22:27:09 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include<is_char.h>

void	skip_whitespace(char **line)
{
	while (**line && is_whitespace((unsigned char)**line))
		(*line)++;
}
