/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:10:56 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/13 13:51:08 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static double	calculate_max_length(t_aux *aux)
{
	double	x;
	double	y;
	double	z;

	x = aux->max_x;
	y = aux->max_y;
	z = aux->max_z;
	return (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

void	move_coordinate(t_aux *aux)
{
	int		i;
	int		j;
	double	ratio;

	i = 0;
	ratio = WINDOW_WIDTH * (0.9 + aux->multi) / calculate_max_length(aux);
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			aux->axis_data[i][j][0] = floor(aux->axis_data[i][j][0] * ratio)
				+ WINDOW_WIDTH / 2 + aux->trans_x;
			aux->axis_data[i][j][1] = floor(aux->axis_data[i][j][1] * ratio)
				+ WINDOW_HEIGHT / 2 + aux->trans_y;
			j++;
		}
		i++;
	}
}
