/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_swap_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:46:19 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 16:38:18 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_if_over_three(t_node **stack_a)
{
	t_node	*tail;
	t_node	*tail_left;
	t_node	*tail_left_left;

	tail = (*stack_a)->left;
	tail_left = tail->left;
	tail_left_left = tail->left->left;
	tail->right = tail_left;
	tail->left = tail_left_left;
	tail_left->right = *stack_a;
	tail_left->left = tail;
	(*stack_a)->left = tail_left;
	tail_left_left->right = tail;
}

static void	swap_if_three(t_node **stack_a)
{
	t_node	*tail;
	t_node	*tail_left;

	tail = (*stack_a)->left;
	tail_left = tail->left;
	(*stack_a)->right = tail;
	(*stack_a)->left = tail_left;
	tail_left->right = *stack_a;
	tail_left->left = tail;
	tail->right = tail_left;
	tail->left = *stack_a;
}

void	swap_a(t_node **stack_a, int flag)
{
	t_node	*tail;
	t_node	*tail_left;

	if (*stack_a == NULL || *stack_a == (*stack_a)->right)
		return ;
	if (flag == 0)
		write(1, "sa\n", 3);
	tail = (*stack_a)->left;
	tail_left = tail->left;
	if (tail_left == *stack_a)
		*stack_a = (*stack_a)->left;
	else if (tail_left->left == *stack_a)
		swap_if_three(stack_a);
	else
		swap_if_over_three(stack_a);
}
