/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:08:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/26 22:46:55 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/get_next_line.h"
#include "../mlx/mlx.h"
#include <stdio.h>

#define X_EVENT_KEY_PRESS	2

#define KEY_ESC	53

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
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
	ratio = 1000 * 0.9 / calculate_max_length(aux);
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			aux->axis_data[i][j][0] = floor(aux->axis_data[i][j][0] * ratio) + 500;
			aux->axis_data[i][j][1] = floor(aux->axis_data[i][j][1] * ratio) + 500;
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
	while (i < aux->row_num) // 11
	{
		j = 0;
		while (j < aux->col_num[0]) // 20
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

void	rotate_z(t_aux *aux)
{
	int	i;
	int	j;
	double x;
	double y;
	double angle;

	i = 0;
	angle = 90 * M_PI / 180;
	while (i < aux->row_num) // y
	{
		j = 0;
		while (j < aux->col_num[0]) // x
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

int	main(int argc, char *argv[])
{
	t_mlx		mlx;
	t_aux		aux;
	t_vector	vector;
	t_img		img;

	if (argc != 2)
		exit(EXIT_FAILURE);
	init_aux(&aux); // init_struct
	if (read_map(argv[1], &aux) == 0)
	{
		free_aux(&aux);
		exit(EXIT_FAILURE); // 파일이 없는 경우, 동적할당 실패 시
	}
	translate_coordinate(&aux);
	project_coordinate(&aux, &vector);
	rotate_coordinate(&aux);
	rotate_z(&aux);
	move_coordinate(&aux);
	print_arr(&aux);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1000, 1000, "mlx_project");
	img.img_ptr = mlx_new_image(mlx.mlx, 1000, 1000); // 이미지 크기에 따라 size_l이 변경
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	draw_dots(&aux, &img);
	draw_lines(&aux, &img);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img_ptr, 0, 0);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &mlx);
	mlx_loop(mlx.mlx);
	free_aux(&aux);
	// system("leaks fdf");
	return (0);
}
