/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:46:41 by mickmart          #+#    #+#             */
/*   Updated: 2024/11/06 09:46:43 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	char	*start;

	start = dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (start);
}

/*
int	main(void)
{
  char dest[10]="helloj";
  const char src[10]="hello";
  ft_strlcpy(dest, src, 0);
  strlcpy(dest, src, 0);
  return (0);
}
*/
