/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:14:33 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 19:40:21 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static void	draw_axis_x(t_aux *aux, t_img *img, int i, int j)
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

static void	draw_axis_y(t_aux *aux, t_img *img, int i, int j)
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
