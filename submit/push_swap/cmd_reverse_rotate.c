/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_reverse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:14:53 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/07 14:03:13 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_a(t_node **stack_a, int flag)
{
	if (*stack_a == NULL)
		return ;
	if (flag == 0)
		write(1, "ra\n", 3);
	*stack_a = (*stack_a)->left;
}

void	rotate_b(t_node **stack_b, int flag)
{
	if (*stack_b == NULL)
		return ;
	if (flag == 0)
		write(1, "rb\n", 3);
	*stack_b = (*stack_b)->left;
}

void	rotate_r(t_node **stack_a, t_node **stack_b, int flag)
{
	if (*stack_a == NULL || *stack_b == NULL)
		return ;
	if (flag == 0)
		write(1, "rr\n", 3);
	rotate_a(stack_a, 1);
	rotate_b(stack_b, 1);
}	
