/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:58:35 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/24 19:15:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/get_next_line.h"

void	calculate_normal_vector(t_angle *a, t_vector *vec)
{
	a->theta = a->theta * M_PI / 180;
	a->phi = a->phi * M_PI / 180;
	vec->a = cos(a->phi) * sin(a->theta);
	vec->b = sin(a->phi) * sin(a->theta);
	vec->c = cos(a->theta);
}

void	calculate_coordinate(double ***axis, t_vector *vec, int row, int *col)
{
	int	i;
	int	j;

	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col[0])
		{
			axis[i][j][3] = -1 * (vec->a * axis[i][j][0] \
			+ vec->b * axis[i][j][1] + vec->c * axis[i][j][2]);
			axis[i][j][0] = vec->a * axis[i][j][3] + axis[i][j][0];
			axis[i][j][1] = vec->b * axis[i][j][3] + axis[i][j][1];
			axis[i][j][2] = vec->c * axis[i][j][3] + axis[i][j][2];
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

void	rotate_z(t_aux *aux, t_angle *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			aux->axis_data[i][j][0] = cos(a->phi) * aux->axis_data[i][j][0]
			+ -1 * sin(a->phi) * aux->axis_data[i][j][1];
			aux->axis_data[i][j][1] = sin(a->phi) * aux->axis_data[i][j][0]
			+ cos(a->phi) * aux->axis_data[i][j][1];
			j++;
		}
		i++;
	}
}

void	rotate_y(t_aux *aux, t_angle *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			aux->axis_data[i][j][0] = cos(a->theta) * aux->axis_data[i][j][0]
			+ -1 * sin(a->theta) * aux->axis_data[i][j][2];
			aux->axis_data[i][j][2] = sin(a->theta) * aux->axis_data[i][j][0]
			+ cos(a->theta) * aux->axis_data[i][j][2];
			j++;
		}
		i++;
	}
}

void	translate_coordinate(t_aux *aux)
{
	double	x_move;
	double	y_move;
	double	z_move;
	int	i;
	int	j;

	x_move = aux->row_num / 2;
	y_move = aux->col_num[0] / 2;
	z_move = find_maximum_z(aux) + find_minimum_z(aux) / 2;
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

void	transform_coordinate(t_aux *aux, t_angle *angle, t_vector *vector)
{
	angle->theta = 90 - 35.264;
	angle->phi = 45;
	calculate_normal_vector(angle, vector);
	calculate_coordinate(aux->axis_data, vector, aux->row_num, aux->col_num);
}

void	rotate_coordinate(t_aux *aux, t_angle *angle)
{
	rotate_z(aux, angle);
	rotate_y(aux, angle);
}