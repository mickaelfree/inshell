/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:16:18 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/29 19:25:23 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

/** @name SINGLYCHAINEDLIST**
** @brief a simple chained list struct.
* @param content: current node
* @param next: next node
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/** @name FT_LSTADD_BACK**
** @brief add a node from the back of the list.
**
** @param lst: the parent list.
** @param new: the node to add.
** @return nothing.
*/
void				ft_lstadd_back(t_list **lst, t_list *new_node);

/** @name FT_LSTADD_FRONT**
** @brief add a node to the front of the list.
**
** @param lst: the parent list.
** @param new: the node to add.
** @return nothing.
*/
void				ft_lstadd_front(t_list **lst, t_list *new_node);

/** @name FT_LSTCLEAR**
** @brief clear and free all node of a chained list.
**
** @param lst: the list.
** @param del: the function to del.
** @return nothing.
*/
void				ft_lstclear(t_list **lst, void (*del)(void *));

/** @name FT_LSTDELONE**
** @brief clear and free a node.
**
** @param lst: the list.
** @param del: the function to del.
** @return nothing.
*/
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/** @name FT_LSTITER**
** @brief Iterates the list ’lst’ and applies the function ’f’
on the content of each node.
**
** @param lst: the address of a pointer to a node.
** @param f: The address of the function used to iterate on the list.
** @return nothing.
*/
void				ft_lstiter(t_list *lst, void (*f)(void *));

/** @name FT_LSTLAST**
** @brief Returns the last node of the list.
**
** @param lst: The beginning of the list.
** @return The length of the list
*/
t_list				*ft_lstlast(t_list *lst);

/** @name FT_LSTSIZE**
** @brief Counts the number of nodes in a list.
**
** @param lst: The beginning of the list.
** @return The length of the list
*/
int					ft_lstsize(t_list *lst);

/** @name FT_LSTMAP**
** @brief Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.
**
** @param lst: The beginning of the list.
** @param f: The address of the function used to iterate on the list.
** @param del: The address of the function used to delete
the content of a node if needed.
** @return The new list. NULL if the allocation fails.
*/
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/** FT_LSTNEW**
** @brief Allocates (with malloc(3)) and returns a new node.
**
** @param content: content of the new node.
** @return the created chained node.
*/
t_list				*ft_lstnew(void *content);

#endif