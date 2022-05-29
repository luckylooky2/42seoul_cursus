/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:52:25 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 11:54:51 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_all(t_mlx **mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*mlx)->aux.row_num)
	{
		j = 0;
		while (j < (*mlx)->aux.col_num[0])
		{
			free((*mlx)->aux.axis_data[i][j]);
			free((*mlx)->aux.map_data[i][j]);
			j++;
		}
		free((*mlx)->aux.axis_data[i]);
		free((*mlx)->aux.map_data[i]);
		i++;
	}
	free((*mlx)->aux.axis_data);
	free((*mlx)->aux.map_data);
	free((*mlx)->aux.col_num);
	free((*mlx)->img.img_ptr);
	free((*mlx)->img.data);
}

void	free_array(char ***double_array, char **single_array)
{
	int	i;

	i = 0;
	if (*double_array != NULL)
	{
		while ((*double_array)[i])
		{
			free((*double_array)[i]);
			i++;
		}
		free(*double_array);
		*double_array = NULL;
	}
	if (*single_array != NULL)
	{
		free(*single_array);
		*single_array = NULL;
	}
}
