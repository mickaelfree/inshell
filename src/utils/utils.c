/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:35:38 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/25 17:01:37 by zsonie           ###   ########lyon.fr   */
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

// Join 2 differents strings to one and free the first one, then return the result
char	*ft_strappend_to_line(char *s1, char *s2, size_t bufsize)
{
	char	*result;
	ssize_t	s1len;
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = -1;
	if (!s2)
		return (NULL);
	s1len = 0;
	if (s1)
		s1len = gnl_ft_strlen(s1);
	result = malloc(sizeof(char) * (s1len + bufsize + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	while (++i < s1len)
		result[i] = s1[i];
	while (++j < (ssize_t)bufsize)
		result[(i + j)] = s2[j];
	result[s1len + bufsize] = '\0';
	free(s1);
	return (result);
}
