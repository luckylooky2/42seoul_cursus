/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:03:37 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 19:44:27 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static int	find_maximum_z(t_aux *aux)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = aux->axis_data[0][0][2];
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			if (aux->axis_data[i][j][2] > max)
				max = aux->axis_data[i][j][2];
			j++;
		}
		i++;
	}
	return (max);
}

static int	find_minimum_z(t_aux *aux)
{
	int	i;
	int	j;
	int	min;

	i = 0;
	min = aux->axis_data[0][0][2];
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			if (aux->axis_data[i][j][2] < min)
				min = aux->axis_data[i][j][2];
			j++;
		}
		i++;
	}
	return (min);
}

void	translate_coordinate(t_aux *aux)
{
	double	x_move;
	double	y_move;
	double	z_move;
	int		i;
	int		j;

	aux->max_x = aux->col_num[0] - 1;
	aux->max_y = aux->row_num - 1;
	aux->max_z = find_maximum_z(aux);
	x_move = ((double)(aux->col_num[0]) - 1) / 2;
	y_move = ((double)(aux->row_num) - 1) / 2;
	z_move = ((double)find_maximum_z(aux) + (double)find_minimum_z(aux)) / 2;
	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			aux->axis_data[i][j][0] -= x_move;
			aux->axis_data[i][j][1] -= y_move;
			aux->axis_data[i][j][2] -= z_move;
			j++;
		}
		i++;
	}
}
