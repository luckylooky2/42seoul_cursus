/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:05:09 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 12:18:47 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	calculate_normal_vector(t_aux *aux, t_vector *vector)
{
	vector->a = cos(aux->phi) * sin(aux->theta);
	vector->b = sin(aux->phi) * sin(aux->theta);
	vector->c = cos(aux->theta);
}

static void	calculate_coordinate(t_aux *aux, t_vector *vector)
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

void	project_coordinate(t_aux *aux, t_vector *vector)
{
	calculate_normal_vector(aux, vector);
	calculate_coordinate(aux, vector);
}
