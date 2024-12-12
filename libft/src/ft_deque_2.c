/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:46:39 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:06 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * It deletes and frees every element of the deque. 
 * Finally, it frees the deque.
*/
void	ft_clear_deque(t_deque **dq, void (*del)(void *))
{
	t_node	*cur;
	void	*content;

	if (!*dq)
		return ;
	cur = (*dq)->head;
	while (cur)
	{
		content = ft_dq_pop_head(dq);
		del(content);
		cur = (*dq)->head;
	}
	free(*dq);
}

/**
 * Pop at the front.
 * It gets the head node, deletes it and return its content.
 * The deque must have been initialized with new or NULL
*/
void	*ft_dq_pop_head(t_deque **dq)
{
	t_node	*popped_head;
	t_node	*new_head;
	void	*content;

	if (!*dq || (*dq)->size == 0)
		return (NULL);
	popped_head = (*dq)->head;
	content = popped_head->content;
	new_head = popped_head->next;
	if (new_head)
		new_head->prev = NULL;
	else
		(*dq)->rear = NULL;
	(*dq)->head = new_head;
	popped_head->next = NULL;
	free(popped_head);
	(*dq)->size--;
	return (content);
}

/**
 * Pop at the end
 * It gets the rear node, deletes it and return its content.
 * The deque must have been initialized with new or NULL
*/
void	*ft_dq_pop_rear(t_deque **dq)
{
	t_node	*popped_rear;
	t_node	*new_rear;
	void	*content;

	if (!*dq || (*dq)->size == 0)
		return (NULL);
	popped_rear = (*dq)->rear;
	content = popped_rear->content;
	new_rear = popped_rear->prev;
	if (new_rear)
		new_rear->next = NULL;
	else
		(*dq)->head = NULL;
	(*dq)->rear = new_rear;
	popped_rear->prev = NULL;
	free(popped_rear);
	(*dq)->size--;
	return (content);
}

/**
 * Iterates the deque ’dq’ and applies the function ’f’ to the content of
 * each element.
*/
void	ft_iter_deque(t_deque *dq, void (*f)(void *))
{
	t_node	*cur;

	if (!f || !dq)
		return ;
	cur = dq->head;
	while (cur)
	{
		f(cur->content);
		cur = cur->next;
	}
}

int	ft_dq_index(t_deque *dq, void *content, int *(*cmp)(void *, void *))
{
	int		i;
	t_node	*cur;

	i = 0;
	cur = dq->head;
	while (cur)
	{
		if (cmp(cur->content, content) == 0)
			return (i);
		i++;
		cur = cur->next;
	}
	return (-1);
}
