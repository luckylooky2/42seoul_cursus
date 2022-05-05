/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:06:01 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 00:34:26 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	is_second_small(t_node **stack_a, t_node **stack_b, t_sort ord)
{
	if (ord.one > ord.two && ord.two < ord.three && ord.three > ord.one)
		swap_a(stack_a, 0);
	else if (ord.one > ord.two && ord.two < ord.three && ord.three < ord.one)
	{
		swap_a(stack_a, 0);
		rotate_a(stack_a, 0);
		swap_a(stack_a, 0);
		reverse_rotate_a(stack_a, 0);
	}
	else if (ord.one > ord.two && ord.two > ord.three)
	{
		swap_a(stack_a, 0);
		push_b(stack_a, stack_b, 0);
		swap_a(stack_a, 0);
		push_a(stack_a, stack_b, 0);
		swap_a(stack_a, 0);
	}	
}

static void	is_second_big(t_node **stack_a, t_node **stack_b, t_sort ord)
{
	if (ord.one < ord.two && ord.three < ord.two && ord.one < ord.three)
	{
		rotate_a(stack_a, 0);
		swap_a(stack_a, 0);
		reverse_rotate_a(stack_a, 0);
	}
	else if (ord.one < ord.two && ord.two > ord.three && ord.three < ord.one)
	{
		push_b(stack_a, stack_b, 0);
		swap_a(stack_a, 0);
		rotate_a(stack_a, 0);
		push_a(stack_a, stack_b, 0);
		reverse_rotate_a(stack_a, 0);
	}
}

void	sort_three(t_node **stack_a, t_node **stack_b, int num)
{
	t_sort	ord;

	ord.one = (*stack_a)->left->idx;
	ord.two = (*stack_a)->left->left->idx;
	ord.three = (*stack_a)->left->left->left->idx;
	if (num <= 2)
	{
		if (ord.one > ord.two)
			swap_a(stack_a, 0);
	}
	else if (ord.one < ord.two)
		is_second_big(stack_a, stack_b, ord);
	else
		is_second_small(stack_a, stack_b, ord);
}
