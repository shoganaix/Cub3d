/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:45:52 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:14 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * Deletes and frees the given element and every successor of that element,
 * using the function ’del’ and free(3). Finally, the pointer to the list must
 * be set to NULL.
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*next;

	if (!*lst)
		return ;
	cur = *lst;
	while (cur)
	{
		next = cur->next;
		ft_lstdelone(cur, del);
		cur = next;
	}
	*lst = 0;
}

/**
 * It takes a node 'lst' as parameter  and free its memory using 
 * the function 'del' given as parameter, it also frees the node.
 * The memory of 'next' is not liberated.
 * 
 * @param lst the node to free
 * @param del pointer to a funtion that frees the content of the node
 * 
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

/**
 * Iterates the list ’lst’ and applies the function ’f’ to the content of
 * each element.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/**
 * Iterates the list ’lst’ and applies the function ’f’ to the content of
 * each element. Creates a new list resulting of the successive applications of
 * the function ’f’. The ’del’ function is used to delete the content of an
 * element if needed.
 * 
 * @param lst 	a node pointer
 * @param f 	the address of a pointer of a function to apply to every 
 * 				element of the list in every iteration.
 * @param del 	un puntero a función utilizado para eliminar
 * 				el contenido de un nodo, si es necesario.
 * @return	La nueva lista.
 * 			NULL si falla la reserva de memoria.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*aux;
	t_list	*prev;
	void	*faux;

	newlst = 0;
	while (lst)
	{
		faux = f(lst->content);
		aux = ft_lstnew(faux);
		if (!aux)
		{
			ft_lstclear(&newlst, del);
			del(faux);
			return (0);
		}
		if (!newlst)
			newlst = aux;
		else
			prev->next = aux;
		prev = aux;
		lst = lst->next;
	}
	return (newlst);
}

int	ft_lstindex(t_list *lst, void *content, int (*cmp)(void *, void *))
{
	int	i;

	i = 0;
	while (lst)
	{
		if (cmp(lst->content, content) == 0)
			return (i);
		i++;
		lst = lst->next;
	}
	return (-1);
}
