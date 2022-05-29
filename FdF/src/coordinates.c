/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:58:35 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 07:09:14 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	calculate_normal_vector(t_aux *aux, t_vector *vector)
{
	vector->a = cos(aux->phi) * sin(aux->theta);
	vector->b = sin(aux->phi) * sin(aux->theta);
	vector->c = cos(aux->theta);
}

void	calculate_coordinate(t_aux *aux, t_vector *vector)
{
	double	x;
	double	y;
	double	z;
	int		i;
	int		j;

	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			x = (aux->axis_data)[i][j][0];
			y = (aux->axis_data)[i][j][1];
			z = (aux->axis_data)[i][j][2];
			aux->axis_data[i][j][3] = -1 * (vector->a * x + vector->b * y
					+ vector->c * z);
			aux->axis_data[i][j][0] = vector->a * aux->axis_data[i][j][3] + x;
			aux->axis_data[i][j][1] = vector->b * aux->axis_data[i][j][3] + y;
			aux->axis_data[i][j][2] = vector->c * aux->axis_data[i][j][3] + z;
			j++;
		}
		i++;
	}
}

int	find_maximum_z(t_aux *aux)
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

int	find_minimum_z(t_aux *aux)
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

void	project_coordinate(t_aux *aux, t_vector *vector)
{
	calculate_normal_vector(aux, vector);
	calculate_coordinate(aux, vector);
}

void	rotate_coordinate(t_aux *aux)
{
	double	x;
	double	y;
	double	z;
	int		i;
	int		j;

	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			x = (aux->axis_data)[i][j][0];
			y = (aux->axis_data)[i][j][1];
			z = (aux->axis_data)[i][j][2];
			(aux->axis_data)[i][j][0] = cos(aux->theta) * cos(aux->phi) * x
				+ cos(aux->theta) * sin(aux->phi) * y - sin(aux->theta) * z;
			(aux->axis_data)[i][j][1] = -sin(aux->phi) * x + cos(aux->phi) * y;
			(aux->axis_data)[i][j][2] = sin(aux->theta) * cos(aux->phi) * x
				+ sin(aux->theta) * sin(aux->phi) * y + cos(aux->theta) * z;
			j++;
		}
		i++;
	}
}
