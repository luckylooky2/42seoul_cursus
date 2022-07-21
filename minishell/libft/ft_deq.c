/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:54:47 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/22 20:50:42 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_deq	*ft_deq_new(void)
{
	t_deq	*deque;

	deque = (t_deq *) malloc(sizeof(t_deq));
	if (deque == 0)
		return (0);
	deque->size = 0;
	deque->tail = (t_gnode *) malloc(sizeof(t_gnode));
	if (deque->tail == 0)
	{
		free(deque);
		return (0);
	}
	deque->tail->prev = deque->tail;
	deque->tail->next = deque->tail;
	deque->tail->data = NULL;
	return (deque);
}

void	ft_deq_delete(t_deq **deque, void del(void *))
{
	t_gnode	*curr;
	t_gnode	*next;

	if (deque && *deque)
	{
		curr = (*deque)->tail->next;
		while (curr != (*deque)->tail)
		{
			next = curr->next;
			del(curr->data);
			free(curr);
			curr = next;
		}
		free((*deque)->tail);
		free(*deque);
		*deque = 0;
	}
}

t_deq	*ft_deq_copy(t_deq *deque, void *copy(void *), void del(void *))
{
	t_deq	*new;
	t_gnode	*node;

	new = ft_deq_new();
	if (new == 0)
		return (0);
	node = deque->tail->next;
	while (node != deque->tail)
	{
		if (ft_deq_push_back(new, copy(node->data)) == -1)
		{
			ft_deq_delete(&new, del);
			return (0);
		}
		node = node->next;
	}
	return (new);
}

int	ft_deq_is_empty(t_deq *deque)
{
	if (deque->size > 0)
		return (0);
	else
		return (1);
}

t_gnode	*ft_deq_get(t_deq *deque, size_t index)
{
	t_gnode	*curr;
	size_t	i;

	if (deque->size <= index)
		return (0);
	if (index < deque->size / 2)
	{
		i = 0;
		curr = deque->tail->next;
		while (i++ < index)
			curr = curr->next;
	}
	else
	{
		i = deque->size - 1;
		curr = deque->tail->prev;
		while (index < i--)
			curr = curr->prev;
	}
	return (curr);
}
