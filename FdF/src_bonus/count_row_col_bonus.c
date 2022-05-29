/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_row_col_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:51:35 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 19:40:11 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

int	count_row_num(char *file, t_aux *aux, t_map *map)
{
	char	*line;

	map->fd = open(file, O_RDONLY);
	if (map->fd < 0)
	{
		map->map_status = -1;
		return (map->map_status);
	}
	while (1)
	{
		line = get_next_line(map->fd);
		if (line == NULL)
			break ;
		(aux->row_num)++;
		free(line);
	}
	close(map->fd);
	if (aux->row_num == 0)
	{
		map->map_status = -2;
		return (map->map_status);
	}
	map->fd = open(file, O_RDONLY);
	return (map->map_status);
}

int	count_col_num(char **array)
{
	int	cnt;

	cnt = 0;
	while (array[cnt])
		cnt++;
	return (cnt);
}

int	check_col_num(int **col_num, int row_num, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < row_num - 1)
	{
		j = i + 1;
		while (j < row_num)
		{
			if ((*col_num)[i] != (*col_num)[j])
			{
				map->map_status = -3;
				return (-3);
			}
			j++;
		}
		i++;
	}
	return (1);
}
