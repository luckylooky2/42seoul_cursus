/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:12:07 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/21 22:58:48 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/get_next_line.h"

int	read_map(char *file, t_aux *aux)
{
	int		fd;
	int		i;
	int 	j;
	char	**lines;
	char 	**tmp;

	i = 0;
	if (count_row_num(file, aux) == 0) // row 개수 count
		return (0);
	fd = open(file, O_RDONLY);
	aux->axis_data = (double ***)malloc(sizeof(double **) * aux->row_num); // 좌표 3차원 배열
	if (aux->axis_data == NULL)
		return (0);
	aux->col_num = (int *)malloc(sizeof(int) * aux->row_num);
	lines = (char **)malloc(sizeof(char *) * (aux->row_num + 1));
	while (1)
	{
		j = 0;
		lines[i] = get_next_line(fd);
		if (lines[i] == NULL)
			break ;
		tmp = ft_split(lines[i], ' ');
		(aux->col_num)[i] = count_col_num(tmp);
		(aux->axis_data)[i] = (double **)malloc(sizeof(double *) * (aux->col_num)[i]); // 좌표 2차원 배열
		while (tmp[j])
		{
			(aux->axis_data)[i][j] = (double *)malloc(sizeof(double) * 4); // 좌표 1차원 배열
			(aux->axis_data)[i][j][0] = i; // x좌표?
			(aux->axis_data)[i][j][1] = j; // y좌표?
			(aux->axis_data)[i][j][2] = ft_atoi(tmp[j]);
			(aux->axis_data)[i][j][3] = 0;
			j++;
		}
		free_double_array(&tmp);
		i++;
	}
	free_double_array(&lines);
	if (check_col_num(&aux->col_num, aux->row_num) == 0)
		return (0);
	return (1);
}

