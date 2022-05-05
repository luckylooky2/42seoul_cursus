/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_b_to_a_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:54:14 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 16:39:33 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_index(t_node **stack_b, int num, int flag)
{
	t_node	*curr;
	int		big;
	int		small;
	int		cnt;

	if (num == 0)
		return (0);
	cnt = 1;
	curr = (*stack_b)->left;
	big = curr->idx;
	small = curr->idx;
	curr = curr->left;
	while (cnt < num)
	{
		if (curr->idx > big)
			big = curr->idx;
		if (curr->idx < small)
			small = curr->idx;
		cnt++;
		curr = curr->left;
	}
	if (flag == 1)
		return (big);
	return (small);
}

int	check_sorted(t_node **stack, int num)
{
	t_node	*prev;
	t_node	*next;
	int		cnt;
	int		res;

	prev = (*stack)->left;
	next = (*stack)->left->left;
	cnt = 0;
	res = 0;
	while (cnt < num)
	{
		if (prev->idx + 1 == next->idx)
			res++;
		prev = prev->left;
		next = next->left;
		cnt++;
	}
	if (cnt == res)
		return (1);
	return (0);
}

int	set_pivot(t_node **stack, int num, int flag)
{
	int	max;
	int	min;

	max = find_index(stack, num, 1);
	min = find_index(stack, num, 0);
	if (flag == 1)
		return (min + (max - min) * 0.75);
	else
		return (min + (max - min) * 0.5);
}
