/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_swap_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:17 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 16:38:42 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_if_over_three(t_node **stack_b)
{
	t_node	*tail;
	t_node	*tail_left;
	t_node	*tail_left_left;

	tail = (*stack_b)->left;
	tail_left = tail->left;
	tail_left_left = tail->left->left;
	tail->right = tail_left;
	tail->left = tail_left_left;
	tail_left->right = *stack_b;
	tail_left->left = tail;
	(*stack_b)->left = tail_left;
	tail_left_left->right = tail;
}

static void	swap_if_three(t_node **stack_b)
{
	t_node	*tail;
	t_node	*tail_left;

	tail = (*stack_b)->left;
	tail_left = tail->left;
	(*stack_b)->right = tail;
	(*stack_b)->left = tail_left;
	tail_left->right = *stack_b;
	tail_left->left = tail;
	tail->right = tail_left;
	tail->left = *stack_b;
}

void	swap_b(t_node **stack_b, int flag)
{
	t_node	*tail;
	t_node	*tail_left;

	if (*stack_b == NULL || *stack_b == (*stack_b)->right)
		return ;
	if (flag == 0)
		write(1, "sb\n", 3);
	tail = (*stack_b)->left;
	tail_left = tail->left;
	if (tail_left == *stack_b)
		*stack_b = (*stack_b)->left;
	else if (tail_left->left == *stack_b)
		swap_if_three(stack_b);
	else
		swap_if_over_three(stack_b);
}
