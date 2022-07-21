/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:54:47 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/22 20:50:42 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_deque	*ft_deque_new(void)
{
	t_deque	*deque;

	deque = (t_deque *) malloc(sizeof(t_deque));
	if (deque == 0)
		return (0);
	deque->size = 0;
	deque->tail = (t_node *) malloc(sizeof(t_node));
	if (deque->tail == 0)
	{
		free(deque);
		return (0);
	}
	deque->tail->prev = deque->tail;
	deque->tail->next = deque->tail;
	deque->tail->num = -1;
	return (deque);
}

void	ft_deque_delete(t_deque **deque)
{
	t_node	*curr;
	t_node	*next;

	if (deque && *deque)
	{
		curr = (*deque)->tail->next;
		while (curr != (*deque)->tail)
		{
			next = curr->next;
			free(curr);
			curr = next;
		}
		free((*deque)->tail);
		free(*deque);
		*deque = 0;
	}
}

t_deque	*ft_deque_copy(t_deque *deque)
{
	t_deque	*new;
	t_node	*node;

	new = ft_deque_new();
	if (new == 0)
		return (0);
	node = deque->tail->next;
	while (node != deque->tail)
	{
		if (ft_deque_push_back(new, node->num) == -1)
		{
			ft_deque_delete(&new);
			return (0);
		}
		node = node->next;
	}
	return (new);
}

int	ft_deque_is_empty(t_deque *deque)
{
	if (deque->size > 0)
		return (0);
	else
		return (1);
}

t_node	*ft_deque_get(t_deque *deque, size_t index)
{
	t_node	*curr;
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
