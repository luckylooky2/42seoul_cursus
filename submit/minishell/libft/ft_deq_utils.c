/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deq_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:03:15 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/22 21:17:16 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_deq_push_front(t_deq *deque, void *data)
{
	t_gnode	*new_node;

	new_node = (t_gnode *) malloc(sizeof(t_gnode));
	if (new_node == 0)
		return (-1);
	new_node->data = data;
	new_node->next = deque->tail->next;
	new_node->prev = deque->tail;
	new_node->next->prev = new_node;
	deque->tail->next = new_node;
	deque->size++;
	return (0);
}

int	ft_deq_push_back(t_deq *deque, void *data)
{
	t_gnode	*new_node;

	new_node = (t_gnode *) malloc(sizeof(t_gnode));
	if (new_node == 0)
		return (-1);
	new_node->data = data;
	new_node->prev = deque->tail->prev;
	new_node->next = deque->tail;
	new_node->prev->next = new_node;
	deque->tail->prev = new_node;
	deque->size++;
	return (0);
}

void	*ft_deq_pop_front(t_deq *deque)
{
	t_gnode	*node;
	void	*data;

	node = deque->tail->next;
	data = node->data;
	deque->tail->next = node->next;
	node->next->prev = deque->tail;
	free(node);
	deque->size--;
	return (data);
}

void	*ft_deq_pop_back(t_deq *deque)
{
	t_gnode	*node;
	void	*data;

	node = deque->tail->prev;
	data = node->data;
	deque->tail->prev = node->prev;
	node->prev->next = deque->tail;
	free(node);
	deque->size--;
	return (data);
}

void	ft_deq_swap(t_deq *deque, size_t i, size_t j)
{
	t_gnode	*node_i;
	t_gnode	*node_j;
	void	*temp;

	node_i = ft_deq_get(deque, i);
	node_j = ft_deq_get(deque, j);
	if (node_i == 0 || node_j == 0)
		return ;
	temp = node_i->data;
	node_i->data = node_j->data;
	node_j->data = temp;
}
