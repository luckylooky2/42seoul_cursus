/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:03:15 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/22 21:17:16 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_deque_push_front(t_deque *deque, int num)
{
	t_node	*new_node;

	new_node = (t_node *) malloc(sizeof(t_node));
	if (new_node == 0)
		return (-1);
	new_node->num = num;
	new_node->next = deque->tail->next;
	new_node->prev = deque->tail;
	new_node->next->prev = new_node;
	deque->tail->next = new_node;
	deque->size++;
	return (0);
}

int	ft_deque_push_back(t_deque *deque, int num)
{
	t_node	*new_node;

	new_node = (t_node *) malloc(sizeof(t_node));
	if (new_node == 0)
		return (-1);
	new_node->num = num;
	new_node->prev = deque->tail->prev;
	new_node->next = deque->tail;
	new_node->prev->next = new_node;
	deque->tail->prev = new_node;
	deque->size++;
	return (0);
}

int	ft_deque_pop_front(t_deque *deque)
{
	t_node	*node;
	int		num;

	node = deque->tail->next;
	num = node->num;
	deque->tail->next = node->next;
	node->next->prev = deque->tail;
	free(node);
	deque->size--;
	return (num);
}

int	ft_deque_pop_back(t_deque *deque)
{
	t_node	*node;
	int		num;

	node = deque->tail->prev;
	num = node->num;
	deque->tail->prev = node->prev;
	node->prev->next = deque->tail;
	free(node);
	deque->size--;
	return (num);
}

void	ft_deque_swap(t_deque *deque, size_t i, size_t j)
{
	t_node	*node_i;
	t_node	*node_j;
	int		temp;

	node_i = ft_deque_get(deque, i);
	node_j = ft_deque_get(deque, j);
	if (node_i == 0 || node_j == 0)
		return ;
	temp = node_i->num;
	node_i->num = node_j->num;
	node_j->num = temp;
}
