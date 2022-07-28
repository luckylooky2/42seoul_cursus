/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_deque.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:57:24 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/27 16:59:38 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//
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
		if (data != NULL)
			ft_deq_push_back(new_deq, data);
	}
	ft_deq_delete(&deq, del);
	return (new_deq);
}