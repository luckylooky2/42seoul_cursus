/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_swap_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:03:44 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/08 15:51:24 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	swap_s(t_node **stack_a, t_node **stack_b, int flag)
{
	if (*stack_a == NULL || *stack_a == (*stack_a)->right
		|| *stack_b == NULL || *stack_b == (*stack_b)->right)
		return ;
	if (flag == 0)
		write(1, "ss\n", 3);
	swap_a(stack_a, 1);
	swap_b(stack_b, 1);
}
