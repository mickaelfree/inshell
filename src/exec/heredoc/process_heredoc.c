/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:58:19 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/28 06:34:54 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>

void	ft_itoa_append(char *dest, int n)
{
	char	*num_str;
	int		i;

	num_str = ft_itoa(n);
	i = 0;
	while (num_str[i])
	{
		dest[i] = num_str[i];
		i++;
	}
	dest[i] = '\0';
	free(num_str);
}

static int	create_temp_file(char *template)
{
	int	fd;
	int	counter;

	counter = 0;
	while (counter < 1000)
	{
		ft_memcpy(template, "/tmp/inshell_heredoc_", 21);
		ft_itoa_append(template + 21, counter);
		fd = open(template, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd != -1)
			return (fd);
		counter++;
	}
	return (-1);
}

char	*process_heredoc(char *delimiter)
{
	char	*line;
	char	template[40];
	int		fd;

	fd = create_temp_file(template);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (ft_strdup(template));
}
