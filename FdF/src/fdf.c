/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:08:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 09:13:22 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

void	control_angle_and_multi(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
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
	{
		if (mlx->aux.multi > -0.9)
			mlx->aux.multi -= 0.01;
	}
}

void	control_axis(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_L_BRACKET)
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
}

int	press_keys(int keycode, t_mlx *mlx)
{
	init_img_data(&mlx->img);
	control_angle_and_multi(keycode, mlx);
	control_axis(keycode, mlx);
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
				+ WINDOW_WIDTH / 2 + aux->trans_y;
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
			if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT && x >= 0 && y >= 0)
				img->data[WINDOW_WIDTH * y + x] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void	draw_axis_x(t_aux *aux, t_img *img, int i, int j)
{
	t_line	line;
	int		cnt;

	line.dx = aux->axis_data[i + 1][j][0] - aux->axis_data[i][j][0];
	line.dy = aux->axis_data[i + 1][j][1] - aux->axis_data[i][j][1];
	if (fabs(line.dx) > fabs(line.dy))
		line.steps = fabs(line.dx);
	else
		line.steps = fabs(line.dy);
	line.x = aux->axis_data[i][j][0];
	line.y = aux->axis_data[i][j][1];
	line.x_incre = (line.dx / line.steps);
	line.y_incre = (line.dy / line.steps);
	cnt = 0;
	while (cnt < line.steps)
	{
		line.x += line.x_incre;
		line.y += line.y_incre;
		if (line.x >= 0 && line.y >= 0
			&& line.x < WINDOW_WIDTH && line.y < WINDOW_HEIGHT)
			img->data[(int)line.x + WINDOW_WIDTH * (int)line.y] = 0xFFFFFF;
		cnt++;
	}
}

void	draw_axis_y(t_aux *aux, t_img *img, int i, int j)
{
	t_line	line;
	int		cnt;

	line.dx = aux->axis_data[i][j + 1][0] - aux->axis_data[i][j][0];
	line.dy = aux->axis_data[i][j + 1][1] - aux->axis_data[i][j][1];
	if (fabs(line.dx) > fabs(line.dy))
		line.steps = fabs(line.dx);
	else
		line.steps = fabs(line.dy);
	line.x = aux->axis_data[i][j][0];
	line.y = aux->axis_data[i][j][1];
	line.x_incre = (line.dx / line.steps);
	line.y_incre = (line.dy / line.steps);
	cnt = 0;
	while (cnt < line.steps)
	{
		line.x += line.x_incre;
		line.y += line.y_incre;
		if (line.x >= 0 && line.y >= 0
			&& line.x < WINDOW_WIDTH && line.y < WINDOW_HEIGHT)
			img->data[(int)line.x + WINDOW_WIDTH * (int)line.y] = 0xFFFFFF;
		cnt++;
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
			if (i < aux->row_num - 1)
				draw_axis_x(aux, img, i, j);
			if (j < aux->col_num[0] - 1)
				draw_axis_y(aux, img, i, j);
			j++;
		}
		i++;
	}
}

// void	print_arr(t_aux *data)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	j = 0;
// 	while (i < data->row_num)
// 	{
// 		j = 0;
// 		while (j < data->col_num[i])
// 		{
// 			printf("(%f, %f, %f)", (data->axis_data)[i][j][0], (data->axis_data)[i][j][1], (data->axis_data)[i][j][2]);
// 			if (j == data->col_num[i] - 1)
// 				printf("\n");
// 			else
// 				printf(" ");
// 			j++;
// 		}
// 		i++;
// 	}
// }

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

void	check_map_status(int map_status, char *argv[])
{
	if (map_status == 1)
		return ;
	else if (map_status == MAP_FAIL_MALLOC)
	{
		perror("Memory allocation Failed.");
		exit(EXIT_FAILURE);
	}
	else if (map_status == MAP_NO_FILE)
	{
		write(2, "No file ", 9);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	else if (map_status == MAP_NO_DATA)
	{
		write(2, "No data found.\n", 16);
		exit(EXIT_FAILURE);
	}
	else if (map_status == MAP_DIFF_COL)
	{
		write(2, "Different number of columns.\n", 30);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	t_mlx		mlx;
	t_aux		aux;
	t_vector	vector;
	t_img		img;
	int			map_status;

	if (argc != 2)
		exit(EXIT_FAILURE);
	init_struct(&aux, &vector);
	map_status = read_map(argv[1], &aux);
	check_map_status(map_status, argv);
	system("leaks fdf");
	init_mlx(&mlx, &aux, &vector, &img);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &press_keys, &mlx);
	mlx_hook(mlx.win, X_EVENT_CLOSE_BUTTON, 0, &close_window, &mlx);
	mlx_loop_hook(mlx.mlx, &repeat_main_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
