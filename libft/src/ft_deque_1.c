/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:46:39 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:05 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_node	*ft_new_node(t_node *prev, void *content, t_node *next)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->prev = prev;
	node->content = content;
	node->next = next;
	return (node);
}

/**
 * Create a new deque.
 * The method creates a new node using malloc. 
 * This node is the head and the rear of the deque
 * and it contains the `content` and points to NULL
 * on both sides.
 * 
 * @param content the content of the node
 * @return a new list with just one node.
*/
t_deque	*ft_new_deque(void)
{
	t_deque	*dq;

	dq = (t_deque *)malloc(sizeof(t_deque));
	if (!dq)
		return (NULL);
	dq->head = NULL;
	dq->rear = NULL;
	dq->size = 0;
	return (dq);
}

/**
 * Append at the end.
 * It adds new element at the end of the deque.
 * The deque must have been initialized with new or NULL
*/
void	ft_dq_append_rear(t_deque **dq, void *new_content)
{
	t_node	*rear;
	t_node	*new_node;

	if (!new_content)
		return ;
	if (!*dq)
	{
		*dq = ft_new_deque();
		if (!*dq)
			return ;
	}
	rear = (*dq)->rear;
	new_node = ft_new_node(rear, new_content, NULL);
	if (rear)
		rear->next = new_node;
	else
		(*dq)->head = new_node;
	(*dq)->rear = new_node;
	(*dq)->size++;
}

/**
 * Append at the front.
 * It adds a new element at the beginning of the deque.
 * The deque must have been initialized with new or NULL
*/
void	ft_dq_append_head(t_deque **dq, void *new_content)
{
	t_node	*head;
	t_node	*new_node;

	if (!new_content)
		return ;
	if (!*dq)
	{
		*dq = ft_new_deque();
		if (!*dq)
			return ;
	}
	head = (*dq)->head;
	new_node = ft_new_node(NULL, new_content, head);
	if (head)
		head->prev = new_node;
	else
		(*dq)->rear = new_node;
	(*dq)->head = new_node;
	(*dq)->size++;
}

/**
 * It counts the number of elements in a deque.
*/
int	ft_deque_count(t_deque *dq)
{
	return (dq->size);
}
