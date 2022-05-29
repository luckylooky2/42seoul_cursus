/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:09:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/29 19:49:25 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../include/get_next_line.h"
# include "../mlx/mlx.h"

# define WINDOW_WIDTH			800
# define WINDOW_HEIGHT			800

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_CLOSE_BUTTON	17

# define KEY_ESC				53
# define KEY_UP					126
# define KEY_DOWN				125
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_PLUS				24
# define KEY_MINUS				27
# define KEY_L_BRACKET			33
# define KEY_R_BRACKET			30
# define KEY_SPACE				49

# define MAP_FAIL_MALLOC		0
# define MAP_NO_FILE			-1
# define MAP_NO_DATA			-2
# define MAP_DIFF_COL			-3

typedef struct s_aux
{
	int		row_num;
	int		*col_num;
	int		max_x;
	int		max_y;
	int		max_z;
	double	***axis_data;
	double	***map_data;
	double	theta;
	double	phi;
	double	multi;
	int		alpha;
	int		trans_x;
	int		trans_y;
}	t_aux;

typedef struct s_vector
{
	double	a;
	double	b;
	double	c;
}	t_vector;

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_aux		aux;
	t_vector	vector;
	t_img		img;
}	t_mlx;

typedef struct s_line
{
	double	dx;
	double	dy;
	int		steps;
	double	x;
	double	y;
	double	x_incre;
	double	y_incre;
}	t_line;

typedef struct s_map
{
	int		fd;
	char	*line;
	char	**tmp;
	int		map_status;
}	t_map;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);

int		count_row_num(char *file, t_aux *aux, t_map *map);
int		count_col_num(char **array);
int		check_col_num(int **col_num, int row_num, t_map *map);

int		read_map(char *file, t_aux *aux);

void	translate_coordinate(t_aux *aux);
void	project_coordinate(t_aux *aux, t_vector *vector);
void	rotate_coordinate(t_aux *aux);
void	rotate_axis_z(t_aux *aux);
void	move_coordinate(t_aux *aux);

void	draw_dots(t_aux *aux, t_img *img);
void	draw_lines(t_aux *aux, t_img *img);

int		press_keys(int keycode, t_mlx *mlx);
int		close_window(t_mlx *mlx);
int		repeat_main_loop(t_mlx *mlx);
void	free_all(t_mlx **mlx);
void	free_array(char ***double_array, char **single_array);

void	init_struct(t_aux *aux, t_vector *vector);
void	init_mlx(t_mlx *mlx, t_aux *aux, t_vector *vector, t_img *img);
void	init_map(t_map *map);
void	init_all_data(t_aux *aux);

#endif