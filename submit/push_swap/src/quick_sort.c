/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:39:24 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/08 15:51:57 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	swap(t_node **array, int i, int j)
{
	t_node	*temp;

	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

static int	partition(t_node **array, int left, int right)
{
	int	pivot;
	int	low;
	int	high;

	pivot = array[left]->data;
	low = left + 1;
	high = right;
	while (low <= high)
	{
		while (low <= right && pivot >= array[low]->data)
			low++;
		while (high >= (left + 1) && pivot <= array[high]->data)
			high--;
		if (low <= high)
			swap(array, low, high);
	}
	swap(array, left, high);
	return (high);
}

static void	quick_sort_recursive(t_node **array, int left, int right)
{
	int	pivot_position;

	if (left >= right)
		return ;
	pivot_position = partition(array, left, right);
	quick_sort_recursive(array, left, pivot_position - 1);
	quick_sort_recursive(array, pivot_position + 1, right);
}

void	quick_sort(t_node **array, int argc)
{
	int	left;
	int	right;

	left = 0;
	right = argc - 2;
	quick_sort_recursive(array, left, right);
}
