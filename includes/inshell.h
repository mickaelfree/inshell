/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:12:48 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 15:45:22 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INSHELL_H
# define INSHELL_H

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

//TODO:
//la stuctur pour le parsing la tokenisation etc
//INFO: header pour les utils

size_t	ft_strlcpy(char *dst, const char *src, size_t sz);
char	**ft_split(char const *s, char c);

#endif 
