/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:12:07 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 20:48:01 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	fill_axis_and_map_data(t_aux *aux, char **tmp, int i, int j)
{
	(aux->axis_data)[i][j][0] = j;
	(aux->axis_data)[i][j][1] = i;
	(aux->axis_data)[i][j][2] = ft_atoi(tmp[j]);
	(aux->axis_data)[i][j][3] = 0;
	(aux->map_data)[i][j][0] = j;
	(aux->map_data)[i][j][1] = i;
	(aux->map_data)[i][j][2] = ft_atoi(tmp[j]);
	(aux->map_data)[i][j][3] = 0;
}

static int	malloc_three_dimension(t_aux **aux, t_map *map)
{
	(*aux)->axis_data = (double ***)ft_calloc(
			sizeof(double **), (*aux)->row_num);
	(*aux)->map_data = (double ***)ft_calloc(
			sizeof(double **), (*aux)->row_num);
	(*aux)->col_num = (int *)ft_calloc(
			sizeof(int), (*aux)->row_num);
	if (!((*aux)->axis_data) || !((*aux)->map_data) || !((*aux)->col_num))
	{
		map->map_status = MAP_FAIL_MALLOC;
		return (MAP_FAIL_MALLOC);
	}
	return (MAP_SUCCESS);
}

static int	malloc_two_dimension(t_aux **aux, t_map *map, int i, int *j)
{
	*j = 0;
	map->line = get_next_line(map->fd);
	if (map->line == NULL)
		return (0);
	map->tmp = ft_split(map->line, ' ');
	if (map->tmp == NULL)
	{
		map->map_status = MAP_FAIL_MALLOC;
		return (MAP_FAIL_MALLOC);
	}
	((*aux)->col_num)[i] = count_col_num(map->tmp);
	((*aux)->axis_data)[i] = (double **)ft_calloc(
			sizeof(double *), ((*aux)->col_num)[i]);
	((*aux)->map_data)[i] = (double **)ft_calloc(
			sizeof(double *), ((*aux)->col_num)[i]);
	if (!(((*aux)->axis_data)[i]) || !(((*aux)->map_data)[i]))
	{
		map->map_status = MAP_FAIL_MALLOC;
		return (MAP_FAIL_MALLOC);
	}
	return (MAP_SUCCESS);
}

static int	malloc_one_dimension(t_aux **aux, t_map *map, int *i, int *j)
{
	while (map->tmp[*j])
	{
		((*aux)->axis_data)[*i][*j] = (double *)ft_calloc(sizeof(double), 4);
		((*aux)->map_data)[*i][*j] = (double *)ft_calloc(sizeof(double), 4);
		if (!(((*aux)->axis_data)[*i][*j]) || !(((*aux)->map_data)[*i][*j]))
		{
			map->map_status = MAP_FAIL_MALLOC;
			return (MAP_FAIL_MALLOC);
		}
		fill_axis_and_map_data(*aux, map->tmp, *i, *j);
		(*j)++;
	}
	(*i)++;
	return (MAP_SUCCESS);
}

int	read_map(char *file, t_aux *aux)
{
	t_map	map;
	int		i;
	int		j;

	i = 0;
	init_map(&map);
	if (count_row_num(file, aux, &map) < 0)
		return (map.map_status);
	if (malloc_three_dimension(&aux, &map) == MAP_FAIL_MALLOC)
		return (MAP_FAIL_MALLOC);
	while (1)
	{
		if (malloc_two_dimension(&aux, &map, i, &j) == MAP_FAIL_MALLOC)
			break ;
		if (malloc_one_dimension(&aux, &map, &i, &j) == MAP_FAIL_MALLOC)
			break ;
		free_array(&map.tmp, &map.line);
	}
	free_array(&map.tmp, &map.line);
	close(map.fd);
	if (map.map_status == MAP_FAIL_MALLOC)
		return (MAP_FAIL_MALLOC);
	if (check_col_num(&aux->col_num, aux->row_num, &map) == MAP_DIFF_COL)
		return (MAP_DIFF_COL);
	return (MAP_SUCCESS);
}
