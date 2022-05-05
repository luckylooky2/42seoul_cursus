/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_swap_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:03:44 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/04 19:05:04 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_s(t_node **stack_a, t_node **stack_b, int flag)
{
	flag = 1;
	if (*stack_a == NULL || *stack_a == (*stack_a)->right
		|| *stack_b == NULL || *stack_b == (*stack_b)->right)
		return ;
	write(1, "ss\n", 3);
	swap_a(stack_a, flag);
	swap_b(stack_b, flag);
}
