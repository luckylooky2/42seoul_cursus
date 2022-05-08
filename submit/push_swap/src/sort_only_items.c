/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_only_items.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:55:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/08 15:52:00 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_only_three(t_node **stack_a)
{
	t_sort	ord;

	ord.one = (*stack_a)->left->idx;
	ord.two = (*stack_a)->right->idx;
	ord.three = (*stack_a)->idx;
	if (ord.one < ord.two && ord.three < ord.two && ord.one < ord.three)
	{
		rotate_a(stack_a, 0);
		swap_a(stack_a, 0);
		reverse_rotate_a(stack_a, 0);
	}
	else if (ord.one < ord.two && ord.two > ord.three && ord.three < ord.one)
		reverse_rotate_a(stack_a, 0);
	else if (ord.one > ord.two && ord.two < ord.three && ord.three > ord.one)
		swap_a(stack_a, 0);
	else if (ord.one > ord.two && ord.two < ord.three && ord.three < ord.one)
		rotate_a(stack_a, 0);
	else if (ord.one > ord.two && ord.two > ord.three)
	{
		rotate_a(stack_a, 0);
		swap_a(stack_a, 0);
	}
}

void	sort_only_four(t_node **stack_a, t_node **stack_b)
{
	int	cnt;

	cnt = 0;
	while (cnt < 4)
	{
		if ((*stack_a)->left->idx == 0)
			push_b(stack_a, stack_b, 0);
		else
			rotate_a(stack_a, 0);
		cnt++;
	}
	sort_only_three(stack_a);
	push_a(stack_a, stack_b, 0);
}

void	sort_only_five(t_node **stack_a, t_node **stack_b)
{
	int	cnt;

	cnt = 0;
	while (cnt < 5)
	{
		if ((*stack_a)->left->idx < 2)
			push_b(stack_a, stack_b, 0);
		else
			rotate_a(stack_a, 0);
		cnt++;
	}
	sort_only_three(stack_a);
	if ((*stack_b)->idx > (*stack_b)->right->idx)
		swap_b(stack_b, 0);
	push_a(stack_a, stack_b, 0);
	push_a(stack_a, stack_b, 0);
}
