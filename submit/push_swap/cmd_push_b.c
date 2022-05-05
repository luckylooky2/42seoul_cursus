/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_push_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 00:03:38 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/04 19:01:50 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_if_over_one(t_node **stack_a, t_node **stack_b)
{
	t_node	*a_tail;
	t_node	*a_tail_left;
	t_node	*b_tail;

	a_tail = (*stack_a)->left;
	a_tail_left = a_tail->left;
	b_tail = (*stack_b)->left;
	b_tail->right = a_tail;
	a_tail->left = b_tail;
	a_tail->right = *stack_b;
	(*stack_b)->left = a_tail;
	if ((*stack_a)->right == *stack_b)
	{
		*stack_a = NULL;
		return ;
	}
	a_tail_left->right = *stack_a;
	(*stack_a)->left = a_tail_left;
}

static void	push_if_one(t_node **stack_a, t_node **stack_b)
{
	t_node	*a_tail;
	t_node	*a_tail_left;
	t_node	*b_tail;

	a_tail = (*stack_a)->left;
	a_tail_left = a_tail->left;
	b_tail = (*stack_b)->left;
	b_tail->left = a_tail;
	a_tail->right = b_tail;
	a_tail->left = b_tail;
	b_tail->right = a_tail;
	if ((*stack_a)->right == *stack_b)
	{
		*stack_a = NULL;
		return ;
	}
	a_tail_left->right = *stack_a;
	(*stack_a)->left = a_tail_left;
}

static void	push_if_null(t_node **stack_a, t_node **stack_b)
{
	t_node	*a_tail;
	t_node	*a_tail_left;
	t_node	*b_tail;	

	a_tail = (*stack_a)->left;
	a_tail_left = a_tail->left;
	b_tail = NULL;
	*stack_b = a_tail;
	a_tail = a_tail->left;
	(*stack_b)->left = *stack_b;
	(*stack_b)->right = *stack_b;
	if (*stack_a == (*stack_a)->right)
	{
		*stack_a = NULL;
		return ;
	}
	a_tail->right = *stack_a;
	(*stack_a)->left = a_tail;
}

void	push_b(t_node **stack_a, t_node **stack_b, int flag)
{
	t_node	*a_tail;
	t_node	*a_tail_left;
	t_node	*b_tail;

	if (*stack_a == NULL)
		return ;
	if (flag == 0)
		write(1, "pb\n", 3);
	a_tail = (*stack_a)->left;
	a_tail_left = a_tail->left;
	b_tail = NULL;
	if (*stack_b == NULL)
		push_if_null(stack_a, stack_b);
	else
	{
		b_tail = (*stack_b)->left;
		if (b_tail == b_tail->right)
			push_if_one(stack_a, stack_b);
		else
			push_if_over_one(stack_a, stack_b);
	}
}
