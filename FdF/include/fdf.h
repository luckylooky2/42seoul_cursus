/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:09:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/27 19:07:37 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>


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

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_aux		aux;
	t_vector	vector;
	t_img		img;
}	t_mlx;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		count_row_num(char *file, t_aux *aux);
int		count_col_num(char **array);
int		check_col_num(int **col_num, int row_num);
void	free_double_array(char ***array);
int		read_map(char *file, t_aux *aux);
void	init_struct(t_aux *aux, t_vector *vector);
void	init_data(t_aux *aux);
void	init_angle(t_aux *aux);
void	free_aux(t_aux *aux);
int		find_maximum_z(t_aux *aux);
int		find_minimum_z(t_aux *aux);

void	translate_coordinate(t_aux *aux);
void	project_coordinate(t_aux *aux, t_vector *vector);
void	calculate_normal_vector(t_aux *aux, t_vector *vector);
void	calculate_coordinate(t_aux *aux, t_vector *vector);
void	rotate_coordinate(t_aux *aux);

int		press_keys(int keycode, t_mlx *mlx);

#endif