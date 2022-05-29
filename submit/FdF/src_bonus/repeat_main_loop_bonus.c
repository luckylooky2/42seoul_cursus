/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_main_loop_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:48:41 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 19:44:15 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static void	init_axis_data(t_aux *aux)
{
	int	i;
	int	j;

	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			(aux->axis_data)[i][j][0] = (aux->map_data)[i][j][0];
			(aux->axis_data)[i][j][1] = (aux->map_data)[i][j][1];
			(aux->axis_data)[i][j][2] = (aux->map_data)[i][j][2];
			(aux->axis_data)[i][j][3] = (aux->map_data)[i][j][3];
			j++;
		}
	i++;
	}
}

int	repeat_main_loop(t_mlx *mlx)
{
	init_axis_data(&mlx->aux);
	translate_coordinate(&mlx->aux);
	project_coordinate(&mlx->aux, &mlx->vector);
	rotate_coordinate(&mlx->aux);
	rotate_axis_z(&mlx->aux);
	move_coordinate(&mlx->aux);
	draw_dots(&mlx->aux, &mlx->img);
	draw_lines(&mlx->aux, &mlx->img);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}
