/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:25:08 by dedme             #+#    #+#             */
/*   Updated: 2025/08/18 18:39:14 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inshell.h"

static char	*get_env_value(char *name, char **envp)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
static char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long		temp;
	int			is_negative;
	long		count_temp;

	is_negative = (n < 0);
	temp = (long)n;
	if (is_negative)
		temp = -temp;
	if (is_negative)
		len = 2;
	else
		len = 1;
	count_temp = temp;
	while (count_temp >= 10)
	{
		count_temp /= 10;
		len++;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (is_negative)
	{
		while (len > 1)
		{
			str[--len] = (temp % 10) + '0';
			temp /= 10;
		}
		str[0] = '-';
	}
	else
	{
		while (len > 0)
		{
			str[--len] = (temp % 10) + '0';
			temp /= 10;
		}
	}
	return (str);
}

char	*ft_parse_name(char *name)
{
	char	*rname;
	int		j;
	int		i;

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
char	*expand_variables(char *str, char **envp)
{
	int		i = 0, j;
	char *status_str;
	int		start;
	char	*var_name;
	char	*value;
	char	*result;


	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) * 4 + 1); // Buffer large
	if (!result)
		return (NULL);
	i = 0,
        j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				// Gestion de $?
                                status_str = ft_itoa(g_last_exit_status);
                                if (status_str)
                                {
                                        ft_strlcpy(result + j, status_str, ft_strlen(status_str) + 1);
                                        j += ft_strlen(status_str);
                                        free(status_str);
                                }
                                i += 2;
	
			}
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			{
				// Variable normale $VAR
				start = i + 1;
				while (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
						+ 1] == '_'))
					i++;
				var_name = strndup(str + start, i + 1 - start);
				value = get_env_value(var_name, envp);
				if (value)
				{
					ft_strlcpy(result + j, value, sizeof(result+j));
					j += strlen(value);
				}
				free(var_name);
				i++;
			}
			else
			{
				result[j++] = str[i++];
			}
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return (result);
}
