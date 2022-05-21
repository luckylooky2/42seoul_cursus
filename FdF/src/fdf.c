/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:08:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/21 22:49:41 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/get_next_line.h"

int	main(int argc, char *argv[])
{
	t_aux	aux;
	// void	*mlx;
	// void	*win;

	if (argc != 2)
		exit(EXIT_FAILURE);
	init_aux(&aux);
	if (read_map(argv[1], &aux) == 0)
	{
		free_aux(&aux);
		system("leaks fdf");
		exit(EXIT_FAILURE); // 파일이 없는 경우, 동적할당 실패 시
	}
	translate_coordinates();
	// mlx = mlx_init();
	// win = mlx_new_window(mlx, 500, 500, "mlx_project");
	// mlx_loop(mlx);
	free_aux(&aux);
	system("leaks fdf");
	return (0);
}
