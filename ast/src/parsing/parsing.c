/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:45:42 by jureix-c          #+#    #+#             */
/*   Updated: 2025/08/31 01:01:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "inshell.h"
#include "libft.h"

/**
 * @brief Reallocates a NULL-terminated list of strings to a larger size.
 *
 * Creates a new array of size @p newsize + 1, duplicates all the existing
 * strings into the new array, and frees the old one.
 *
 * The last element is always set to NULL.
 *
 * @param ptr     Original string array (can be NULL).
 * @param newsize Size of the new array (not counting the NULL terminator).
 * @return Pointer to the newly allocated string array.
 *         Exits via error_exit() if malloc fails.
 */
char	**realloc_list(char **ptr, size_t newsize)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc((newsize + 1) * sizeof(char *));
	while (ptr[i])
	{
		res[i] = ft_strdup(ptr[i]);
		i++;
	}
	if (!res)
		error_exit();
	if (ptr)
		ft_free(ptr);
	return (res);
}

/**
 * @brief Adds a string to a dynamic NULL-terminated array of strings.
 *
 * If the list is NULL, it initializes it with space for one string and
 * a NULL terminator. Otherwise, it reallocates the list with space for
 * the new element and a NULL terminator.
 *
 * @param lst    Address of the list to modify.
 * @param string String to add to the list (will be duplicated).
 */
void	add_elem_to_list(char ***lst, char *string)
{
	int	size;

	size = 0;
	if (*lst == NULL)
	{
		*lst = ft_calloc(2, sizeof(char *));
		**lst = ft_strdup(string);
		*(*lst + 1) = NULL;
		return ;
	}
	while ((*lst)[size])
		size++;
	*lst = realloc_list(*lst, size + 1);
	((*lst)[size]) = ft_strdup(string);
	((*lst)[size + 1]) = NULL;
}

/**
 * @brief Extracts a substring from @p input and adds it as a new token.
 *
 * Extracts the substring between @p start and @p end (inclusive),  
 * duplicates it using ft_substr, and appends it to @p arr_tokens.
 *
 * @param arr_tokens Address of the token list.
 * @param input      Original input string.
 * @param start      Pointer to the start of a token within input.
 * @param end        Pointer to the end of a token within input.
 * @return Pointer to the next position on the input string after @p end.
 */
char	*add_token(char ***arr_tokens, char *input, char *start, char *end)
{
	char	*res;

	res = ft_substr(input, start - input, end - start + 1);
	add_elem_to_list(arr_tokens, res);
	free(res);
	return (end + 1);
}

/**
 * @brief Skips over successive instances of a given character in a string.
 *
 * Moves the pointer forward while the current character equals @p charset.
 *
 * Example:
 * - skip_charset("    ls", ' ') → points to "ls".
 *
 * @param str     Input string pointer.
 * @param charset Character to skip.
 * @return Pointer to the first character not equal to @p charset.
 */
char	*skip_charset(char *str, char charset)
{
	while (*str == charset)
		str++;
	return (str);
}

/**
 * @brief Splits an input line into lexical tokens.
 *
 * Tokenizes an input command by handling:
 * - Spaces (skipped).
 * - Redirections: <, <<, >, >>
 * - Pipes: |
 * - Quoted strings (" " or ' '), ensuring tokens are not cut in the middle.
 *
 * Each token is added to @p arr_tokens using @ref add_token.
 *
 * The function frees the original @p input.
 *
 * @param input      Command line input (dynamically allocated).
 * @param arr_tokens Address of the array of tokens to be filled.
 * @return Always returns NULL (since @p arr_tokens is modified in place).
 */
char	*split_to_tokens(char *input, char ***arr_tokens)
{
	char *start_of_token;
	char *end_of_token;

	start_of_token = input;
	while (*start_of_token != '\0')
	{
		start_of_token = skip_charset(start_of_token, ' ');
		end_of_token = start_of_token;
		while (!ft_strchr("> <|\0", *(start_of_token)))
		{
			if (ft_strchr("\"\'", *end_of_token))
				end_of_token = ft_strchr(end_of_token + 1, *end_of_token);
			if (ft_strchr("> <|\0", *(end_of_token + 1)))
				break ;
			end_of_token++;
		}
		if (ft_strchr("<>", *start_of_token)
			&& *start_of_token == *(start_of_token + 1))
			end_of_token++;
		if (*start_of_token != '\0')
			start_of_token = add_token(arr_tokens, input, start_of_token,
					end_of_token);
	}
	free(input);
	return (NULL);
}
