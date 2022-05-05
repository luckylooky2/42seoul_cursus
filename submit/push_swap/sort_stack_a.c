/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:25:19 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 00:48:14 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*sort_stack_a(t_node *stack_a, t_node *stack_b, int num, int argc)
{
	if (num == 2)
	{
		if (stack_a->left->idx > stack_a->idx)
			swap_a(&stack_a, 0);
	}
	if (num == 3)
		sort_only_three(&stack_a);
	else if (num == 4)
		sort_only_four(&stack_a, &stack_b);
	else if (num == 5)
		sort_only_five(&stack_a, &stack_b);
	else
		move_a_to_b(&stack_a, &stack_b, num, argc);
	return (stack_a);
}
