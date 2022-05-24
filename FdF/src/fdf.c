/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:08:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/25 07:54:22 by chanhyle         ###   ########.fr       */
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

void	move_coordinate(t_aux *aux)
{
	int	i;
	int	j;

	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[0])
		{
			aux->axis_data[i][j][0] = floor(aux->axis_data[i][j][0] * 100) + 100;
			aux->axis_data[i][j][1] = floor(aux->axis_data[i][j][1] * 100) + 100;
			// mul = 1000 * 0.9
			j++;
		}
		i++;
	}
}

int	draw_dot(t_aux *aux, int count_h, int count_w)
{
	int	i;
	int	j;

	i = 0;
	while (i < aux->row_num) // 11
	{
		j = 0;
		while (j < aux->col_num[0]) // 20
		{
			if (count_w == aux->axis_data[i][j][0] && count_h == aux->axis_data[i][j][1])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}


//if (line->x < 1000 && line->y < 1000 && line->x >= 0 && line->y >= 0)
//		my_mlx->img.data[line->y * 1000 + line->x] = 0xFFFFFF;

void Set_Pixel(int x, int y, t_img *img)
{
    img->data[x * 1000 + y] = 0xFFFFFF;
}

void DDA(double x1, double y1, double x2, double y2, t_img *img) // dda
{
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
    x_incre = dx / steps;
    y_incre = dy / steps;

    // 시작 좌표 x(=x1), y(=y1)을 칠해준다
    Set_Pixel(round(x), round(y), img);

    for(int i = 0; i < steps; i++){
        x += x_incre;
        y += y_incre;

        Set_Pixel(round(x), round(y), img);
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

int	main(int argc, char *argv[])
{
	t_mlx		mlx;
	t_aux		aux;
	t_vector	vector;
	t_img		img;
	int			count_w;
	int			count_h;

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
	print_arr(&aux);
	// mlx.mlx = mlx_init();
	// mlx.win = mlx_new_window(mlx.mlx, 1000, 1000, "mlx_project");
	// img.img_ptr = mlx_new_image(mlx.mlx, 1000, 1000);
	// img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	move_coordinate(&aux);
	// count_h = -1;
	// while (++count_h < 1000) // 이 방식이 아니라 좌표 데이터를 기반으로 해당 픽셀에 찍는 방식으로 바꿀 것
	// {
	// 	count_w = -1;
	// 	while (++count_w < 1000)
	// 		if (draw_dot(&aux, count_h, count_w) == 1)
	// 			img.data[count_h * 1000 + count_w] = 0xFFFFFF;
	// }
	// DDA(aux.axis_data[0][0][0], aux.axis_data[0][0][1], aux.axis_data[0][1][0], aux.axis_data[0][1][1], &img);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, img.img_ptr, 0, 0);
	// mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &mlx);
	// mlx_loop(mlx.mlx);
	free_aux(&aux);
	// system("leaks fdf");
	return (0);
}
