/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_a_to_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 00:17:17 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 16:41:15 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse(t_node **stack_b, t_aux *aux)
{
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
		if ((*stack_a)->left->idx < aux->big)
		{
			push_b(stack_a, stack_b, 0);
			(aux->pb)++;
			if ((*stack_b)->left->idx >= aux->small)
			{
				rotate_b(stack_b, 0);
				(aux->rb)++;
			}
		}
		else
		{
			rotate_a(stack_a, 0);
			(aux->ra)++;
		}
		aux->cnt++;
	}
}

void	move_a_to_b(t_node **stack_a, t_node **stack_b, int num, int argc)
{
	t_aux	aux;

	init_aux(&aux);
	aux.big = (argc - num) + (num * 0.55);
	aux.small = (argc - num) + (num * 0.4);
	if (num <= 3)
		sort_three(stack_a, stack_b, num);
	else
	{
		sort_main(stack_a, stack_b, num, &aux);
		init_count(&aux);
		reverse(stack_b, &aux);
		move_a_to_b(stack_a, stack_b, aux.ra, argc);
		move_b_to_a(stack_a, stack_b, aux.rb, argc);
		move_b_to_a(stack_a, stack_b, aux.pb - aux.rb, argc);
	}
}
