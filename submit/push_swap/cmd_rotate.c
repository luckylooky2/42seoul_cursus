/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:13:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/07 14:02:16 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate_a(t_node **stack_a, int flag)
{
	if (*stack_a == NULL)
		return ;
	if (flag == 0)
		write(1, "rra\n", 4);
	*stack_a = (*stack_a)->right;
}

void	reverse_rotate_b(t_node **stack_b, int flag)
{
	if (*stack_b == NULL)
		return ;
	if (flag == 0)
		write(1, "rrb\n", 4);
	*stack_b = (*stack_b)->right;
}

void	reverse_rotate_r(t_node **stack_a, t_node **stack_b, int flag)
{
	if (*stack_a == NULL || *stack_b == NULL)
		return ;
	if (flag == 0)
		write(1, "rrr\n", 4);
	reverse_rotate_a(stack_a, 1);
	reverse_rotate_b(stack_b, 1);
}
