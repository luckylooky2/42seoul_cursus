/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:08:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 19:42:18 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static void	check_map_status(int map_status, char *argv[])
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
	init_mlx(&mlx, &aux, &vector, &img);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &press_keys, &mlx);
	mlx_hook(mlx.win, X_EVENT_CLOSE_BUTTON, 0, &close_window, &mlx);
	mlx_loop_hook(mlx.mlx, &repeat_main_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
