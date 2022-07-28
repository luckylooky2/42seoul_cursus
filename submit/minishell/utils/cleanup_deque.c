/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_deque.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:12:50 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/20 00:12:51 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_deq	*cleanup_deque(t_deq *deq, void del(void *))
{
	void	*data;
	t_deq	*new_deq;

	new_deq = ft_deq_new();
	if (new_deq == NULL)
		panic_memory();
	while (!ft_deq_is_empty(deq))
	{
		data = ft_deq_pop_front(deq);
		if (data != NULL && ft_deq_push_back(new_deq, data) == -1)
			panic_memory();
	}
	ft_deq_delete(&deq, del);
	return (new_deq);
}
