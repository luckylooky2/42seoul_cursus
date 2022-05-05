/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_b_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:56:11 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 16:39:50 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse(t_node **stack_a, t_node **stack_b, int num, t_aux *aux)
{
	while (aux->cnt < aux->ra)
	{
		reverse_rotate_r(stack_a, stack_b, 0);
		if (check_sorted(stack_a, num) == 1)
			(aux->sorted)++;
		aux->cnt++;
	}
	while (aux->cnt < aux->rb)
	{
		reverse_rotate_b(stack_b, 0);
		aux->cnt++;
	}
}

static void	sort_main(t_node **stack_a, t_node **stack_b, int num, t_aux *aux)
{
	while (aux->cnt < num)
	{
		if ((*stack_b)->left->idx >= aux->small)
		{
			push_a(stack_a, stack_b, 0);
			(aux->pa)++;
			if (check_sorted(stack_a, num) == 1)
				(aux->sorted)++;
			else
			{
				if ((*stack_a)->left->idx < aux->big)
				{
					rotate_a(stack_a, 0);
					(aux->ra)++;
				}
			}
		}
		else
		{
			rotate_b(stack_b, 0);
			(aux->rb)++;
		}
		aux->cnt++;
	}
}

void	move_b_to_a(t_node **stack_a, t_node **stack_b, int num, int argc)
{
	t_aux	aux;

	init_aux(&aux);
	aux.big = set_pivot(stack_b, num, 1);
	aux.small = set_pivot(stack_b, num, 0);
	if (num == 0)
		return ;
	else if (num == 1)
		push_a(stack_a, stack_b, 0);
	else if (num <= 3)
		sort_reverse_three(stack_a, stack_b, num);
	else
	{
		sort_main(stack_a, stack_b, num, &aux);
		move_a_to_b(stack_a, stack_b, aux.pa - aux.ra - aux.sorted, argc);
		init_count(&aux);
		reverse(stack_a, stack_b, num, &aux);
		move_a_to_b(stack_a, stack_b, aux.ra - aux.sorted, argc);
		move_b_to_a(stack_a, stack_b, aux.rb, argc);
	}
}
