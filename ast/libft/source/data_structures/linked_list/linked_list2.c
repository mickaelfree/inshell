/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:01:55 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:01:55 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*current;

	current = *lst;
	while (current)
	{
		del(current->content);
		prev = current;
		current = current->next;
		free(prev);
	}
	*lst = NULL;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

static inline t_list	*ft_lstmap_free(t_list **nlst, void *c, \
		void (*del)(void *))
{
	del(c);
	ft_lstclear(nlst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;
	void	*content;

	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (ft_lstmap_free(&new_lst, content, del));
		node = ft_lstnew(content);
		if (!node)
			return (ft_lstmap_free(&new_lst, content, del));
		if (!new_lst)
			new_lst = node;
		else
			ft_lstlast(new_lst)->next = node;
		lst = lst->next;
	}
	return (new_lst);
}
