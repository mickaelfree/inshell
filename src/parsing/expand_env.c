/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:25:08 by dedme             #+#    #+#             */
/*   Updated: 2025/08/05 00:13:05 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

char	*ft_parse_name(char *name)
{
	char	*rname;
	int	j;
	int	i;

	j = 0;
	i = 1;
	rname = malloc(sizeof(char) * ft_strlen(name) + 1);
	while (name[i])
		rname[j++] = name[i++];
//	printf("name = %s\n",rname);
	return (rname);
}

char	*expand_env(char *name)
{
	char	*value;
	char	*rname;

	rname = ft_parse_name(name);
	value = getenv(rname);
//	printf("value = %s\n", value);
	return (value);
}
