/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:44:25 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 23:52:37 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	control_angle(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_UP)
		mlx->aux.theta += 1 * M_PI / 180;
	else if (keycode == KEY_DOWN)
		mlx->aux.theta -= 1 * M_PI / 180;
	else if (keycode == KEY_LEFT)
		mlx->aux.phi += 1 * M_PI / 180;
	else if (keycode == KEY_RIGHT)
		mlx->aux.phi -= 1 * M_PI / 180;
	else if (keycode == KEY_L_BRACKET)
		mlx->aux.alpha += 1;
	else if (keycode == KEY_R_BRACKET)
		mlx->aux.alpha -= 1;
	if (mlx->aux.theta > 2 * M_PI)
		mlx->aux.theta -= 2 * M_PI;
	if (mlx->aux.phi > 2 * M_PI)
		mlx->aux.theta -= 2 * M_PI;
	if (mlx->aux.theta < -2 * M_PI)
		mlx->aux.theta += 2 * M_PI;
	if (mlx->aux.phi < -2 * M_PI)
		mlx->aux.theta += 2 * M_PI;
}

static void	control_axis(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
	{
		if (mlx->aux.trans_y > -1000)
			mlx->aux.trans_y -= 1;
	}
	else if (keycode == KEY_S)
	{
		if (mlx->aux.trans_y < 1000)
			mlx->aux.trans_y += 1;
	}
	else if (keycode == KEY_A)
	{
		if (mlx->aux.trans_x > -1000)
			mlx->aux.trans_x -= 1;
	}
	else if (keycode == KEY_D)
	{
		if (mlx->aux.trans_x < 1000)
			mlx->aux.trans_x += 1;
	}
}

static void	control_multi_and_other(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_PLUS)
	{
		if (mlx->aux.multi < 100)
			mlx->aux.multi += 0.01;
	}
	else if (keycode == KEY_MINUS)
	{
		if (mlx->aux.multi > -0.9)
			mlx->aux.multi -= 0.01;
	}
	else if (keycode == KEY_ESC)
	{
		free_all(&mlx);
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_SPACE)
		init_all_data(&mlx->aux);
}

int	press_keys(int keycode, t_mlx *mlx)
{
	init_img_data(&mlx->img);
	control_angle(keycode, mlx);
	control_axis(keycode, mlx);
	control_multi_and_other(keycode, mlx);
	return (0);
}

int	close_window(t_mlx *mlx)
{
	free_all(&mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(EXIT_SUCCESS);
}
