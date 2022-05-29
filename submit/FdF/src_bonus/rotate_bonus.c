/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:58:35 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 19:44:22 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

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

void	rotate_axis_z(t_aux *aux)
{
	int		i;
	int		j;
	double	x;
	double	y;
	double	angle;

	i = 0;
	angle = (90 + aux->alpha) * M_PI / 180;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			x = (aux->axis_data)[i][j][0];
			y = (aux->axis_data)[i][j][1];
			(aux->axis_data)[i][j][0] = cos(angle) * x - sin(angle) * y;
			(aux->axis_data)[i][j][1] = sin(angle) * x + cos(angle) * y;
			j++;
		}
		i++;
	}
}
