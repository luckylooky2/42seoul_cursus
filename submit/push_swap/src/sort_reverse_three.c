/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_reverse_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:19:16 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/08 15:52:03 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	is_second_small(t_node **stack_a, t_node **stack_b, t_sort ord)
{	
	if (ord.one > ord.two && ord.two < ord.three && ord.three > ord.one)
	{
		push_a(stack_a, stack_b, 0);
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		swap_a(stack_a, 0);
		push_a(stack_a, stack_b, 0);
	}
	else if (ord.one > ord.two && ord.two < ord.three && ord.three < ord.one)
	{
		push_a(stack_a, stack_b, 0);
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
	}
	else if (ord.one > ord.two && ord.two > ord.three)
	{
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
	}
}

static void	is_second_big(t_node **stack_a, t_node **stack_b, t_sort ord)
{
	if (ord.one < ord.two && ord.three < ord.two && ord.one < ord.three)
	{
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
	}
	else if (ord.one < ord.two && ord.two > ord.three && ord.three < ord.one)
	{
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
	}
	else if (ord.one < ord.two && ord.two < ord.three)
	{
		rotate_b(stack_b, 0);
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
		reverse_rotate_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
	}
}

void	sort_reverse_three(t_node **stack_a, t_node **stack_b, int num)
{
	t_sort	ord;

	ord.one = (*stack_b)->left->idx;
	ord.two = (*stack_b)->left->left->idx;
	ord.three = (*stack_b)->left->left->left->idx;
	if (num <= 2)
	{
		if (ord.one < ord.two)
			swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
	}
	else if (ord.one < ord.two)
		is_second_big(stack_a, stack_b, ord);
	else
		is_second_small(stack_a, stack_b, ord);
}
