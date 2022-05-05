/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_push_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:16:18 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 16:24:56 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_if_over_one(t_node **stack_a, t_node **stack_b)
{
	t_node	*a_tail;
	t_node	*b_tail;
	t_node	*b_tail_left;

	a_tail = (*stack_a)->left;
	b_tail = (*stack_b)->left;
	b_tail_left = b_tail->left;
	a_tail->right = b_tail;
	b_tail->left = a_tail;
	b_tail->right = *stack_a;
	(*stack_a)->left = b_tail;
	if ((*stack_b)->right == *stack_a)
	{
		*stack_b = NULL;
		return ;
	}
	b_tail_left->right = *stack_b;
	(*stack_b)->left = b_tail_left;
}

static void	push_if_one(t_node **stack_a, t_node **stack_b)
{
	t_node	*a_tail;
	t_node	*b_tail;
	t_node	*b_tail_left;

	a_tail = (*stack_a)->left;
	b_tail = (*stack_b)->left;
	b_tail_left = b_tail->left;
	a_tail->left = b_tail;
	b_tail->right = a_tail;
	b_tail->left = a_tail;
	a_tail->right = b_tail;
	if ((*stack_b)->right == *stack_a)
	{
		*stack_b = NULL;
		return ;
	}
	b_tail_left->right = *stack_b;
	(*stack_b)->left = b_tail_left;
}

static void	push_if_null(t_node **stack_a, t_node **stack_b)
{
	t_node	*b_tail;

	b_tail = (*stack_b)->left;
	*stack_a = b_tail;
	b_tail = b_tail->left;
	(*stack_a)->left = *stack_a;
	(*stack_a)->right = *stack_a;
	if (*stack_b == (*stack_b)->right)
	{
		*stack_b = NULL;
		return ;
	}
	b_tail->right = *stack_b;
	(*stack_b)->left = b_tail;
}

void	push_a(t_node **stack_a, t_node **stack_b, int flag)
{
	t_node	*a_tail;

	if (*stack_b == NULL)
		return ;
	if (flag == 0)
		write(1, "pa\n", 3);
	a_tail = NULL;
	if (*stack_a == NULL)
		push_if_null(stack_a, stack_b);
	else
	{
		a_tail = (*stack_a)->left;
		if (a_tail == a_tail->right)
			push_if_one(stack_a, stack_b);
		else
			push_if_over_one(stack_a, stack_b);
	}
}
