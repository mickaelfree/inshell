/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:12:48 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/26 17:58:28 by mickmart         ###   ########.fr       */
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
//INFO: builtin_echo est un test pour le moment

int	builtin_echo(char **args);
int	builtin_pwd(char **args);

//INFO: header pour les utils

size_t	ft_strlcpy(char *dst, const char *src, size_t sz);
char	**ft_split(char const *s, char c);

#endif 
