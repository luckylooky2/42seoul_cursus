/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:08:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/28 11:07:59 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/get_next_line.h"
#include "../mlx/mlx.h"
#include <stdio.h>

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_CLOSE_BUTTON	17

#define KEY_ESC			53
#define KEY_UP			126
#define KEY_DOWN		125
#define KEY_LEFT		123
#define KEY_RIGHT		124
#define KEY_W			13
#define KEY_A			0
#define KEY_S			1
#define KEY_D			2
#define KEY_PLUS		24
#define KEY_MINUS		27
#define KEY_L_BRACKET	33
#define KEY_R_BRACKET	30
#define KEY_SPACE		49


// 창 크기도 매크로 지정

void	init_img_data(t_img	*img)
{
	int	i;
	while (i < 999 * 999 + 1)
	{
		img->data[i] = 0;
		i++;
	}
}

int	press_keys(int keycode, t_mlx *mlx)
{
	init_img_data(&mlx->img);
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS); // free
	else if (keycode == KEY_UP)
		mlx->aux.theta += 1 * M_PI / 180;
	else if (keycode == KEY_DOWN)
		mlx->aux.theta -= 1 * M_PI / 180;
	else if (keycode == KEY_LEFT)
		mlx->aux.phi += 1 * M_PI / 180;
	else if (keycode == KEY_RIGHT)
		mlx->aux.phi -= 1 * M_PI / 180;
	else if (keycode == KEY_PLUS)
		mlx->aux.multi += 0.01;
	else if (keycode == KEY_MINUS)
		mlx->aux.multi -= 0.01;
	else if (keycode == KEY_L_BRACKET)
		mlx->aux.alpha += 1;
	else if (keycode == KEY_R_BRACKET)
		mlx->aux.alpha -= 1;
	else if (keycode == KEY_W)
		mlx->aux.trans_y -= 1;
	else if (keycode == KEY_S)
		mlx->aux.trans_y += 1;
	else if (keycode == KEY_A)
		mlx->aux.trans_x -= 1;
	else if (keycode == KEY_D)
		mlx->aux.trans_x += 1;
	else if (keycode == KEY_SPACE)
		init_data(&mlx->aux);
	return (0);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

double	calculate_max_length(t_aux *aux)
{
	double	x;
	double	y;
	double	z;

	x = aux->max_x;
	y = aux->max_y;
	z = aux->max_z;
	return	(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

void	move_coordinate(t_aux *aux)
{
	int		i;
	int		j;
	double	ratio;

	i = 0;
	ratio = 1000 * (0.9 + aux->multi) / calculate_max_length(aux);
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			aux->axis_data[i][j][0] = floor(aux->axis_data[i][j][0] * ratio) + 500 + aux->trans_x;
			aux->axis_data[i][j][1] = floor(aux->axis_data[i][j][1] * ratio) + 500 + aux->trans_y;
			j++;
		}
		i++;
	}
}

void	draw_dots(t_aux *aux, t_img *img)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			x = aux->axis_data[i][j][0];
			y = aux->axis_data[i][j][1];
			if (x < 1000 && y < 1000 && x >= 0 && y >= 0)
				img->data[1000 * y + x] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void DDA(double x1, double y1, double x2, double y2, t_img *img){
    // x, y축의 증분
    double dx = x2 - x1;
    double dy = y2 - y1;
    // 총 칠해야 할 픽셀의 가로(y의 경우 세로) 길이
    int steps;
    // 시작점 지정
    double x = x1, y = y1;

    double x_incre, y_incre;

    if(fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else 
        steps = fabs(dy);
    
    // step가 하나 증가할 때 x, y 좌표가 얼마나 증가할지 지정해준다
    x_incre = (dx / steps);
    y_incre = (dy / steps);

    // 시작 좌표 x(=x1), y(=y1)을 칠해준다
	// img->data[y + 1000 * x] = 0xFFFFFF;

    for(int i = 0; i < steps; i +=1){
        x += x_incre;
        y += y_incre;
		if (x >= 0 && y>= 0 && x < 1000 && y < 1000)
			img->data[(int)x + 1000 * (int)y] = 0xFFFFFF;
    }
}

void	draw_lines(t_aux *aux, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			if (j < aux->col_num[0] - 1)
				DDA(aux->axis_data[i][j][0], aux->axis_data[i][j][1], aux->axis_data[i][j + 1][0], aux->axis_data[i][j + 1][1], img);
			if (i < aux->row_num - 1)
				DDA(aux->axis_data[i][j][0], aux->axis_data[i][j][1], aux->axis_data[i + 1][j][0], aux->axis_data[i + 1][j][1], img);
			j++;
		}
		i++;
	}
}

void	print_arr(t_aux *data)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < data->row_num)
	{
		j = 0;
		while (j < data->col_num[i])
		{
			printf("(%f, %f, %f)", (data->axis_data)[i][j][0], (data->axis_data)[i][j][1], (data->axis_data)[i][j][2]);
			if (j == data->col_num[i] - 1)
				printf("\n");
			else
				printf(" ");
			j++;
		}
		i++;
	}
}

void	rotate_axis_z(t_aux *aux)
{
	int	i;
	int	j;
	double x;
	double y;
	double angle;

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

void	init_axis_data(t_aux *aux)
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

int	main(int argc, char *argv[])
{
	t_mlx		mlx;
	t_aux		aux;
	t_vector	vector;
	t_img		img;

	if (argc != 2)
		exit(EXIT_FAILURE);
	init_struct(&aux, &vector);
	if (read_map(argv[1], &aux) == 0)
		exit(EXIT_FAILURE); // 파일이 없는 경우, 동적할당 실패 시
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1000, 1000, "FdF");
	img.img_ptr = mlx_new_image(mlx.mlx, 1000, 1000);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	mlx.aux = aux;
	mlx.vector = vector;
	mlx.img = img; // 함수로 만들기
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &press_keys, &mlx);
	mlx_hook(mlx.win, X_EVENT_CLOSE_BUTTON, 0, &close_window, &mlx);
	mlx_loop_hook(mlx.mlx, &repeat_main_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
