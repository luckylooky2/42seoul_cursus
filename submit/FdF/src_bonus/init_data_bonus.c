/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:56:09 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 23:55:21 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

void	init_struct(t_aux *aux, t_vector *vector)
{
	aux->row_num = 0;
	aux->col_num = NULL;
	aux->max_x = 0;
	aux->max_y = 0;
	aux->max_z = 0;
	aux->map_data = NULL;
	aux->axis_data = NULL;
	aux->theta = acos(1 / sqrt(3));
	aux->phi = atan(1);
	aux->multi = 0;
	aux->alpha = 0;
	aux->trans_x = 0;
	aux->trans_y = 0;
	vector->a = 0;
	vector->b = 0;
	vector->c = 0;
}

void	init_mlx(t_mlx *mlx, t_aux *aux, t_vector *vector, t_img *img)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	img->img_ptr = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->data = (int *)mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_l, &img->endian);
	mlx->aux = *aux;
	mlx->vector = *vector;
	mlx->img = *img;
}

void	init_map(t_map *map)
{
	map->fd = 0;
	map->line = NULL;
	map->tmp = NULL;
	map->map_status = 1;
}

void	init_all_data(t_aux *aux)
{
	aux->theta = acos(1 / sqrt(3));
	aux->phi = atan(1);
	aux->multi = 0;
	aux->alpha = 0;
	aux->trans_x = 0;
	aux->trans_y = 0;
}

void	init_img_data(t_img	*img)
{
	int	i;

	i = 0;
	while (i < (WINDOW_WIDTH - 1) * (WINDOW_HEIGHT - 1) + 1)
	{
		img->data[i] = 0;
		i++;
	}
}
