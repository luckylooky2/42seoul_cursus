/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:09:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/26 17:40:30 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}	t_mlx;

typedef struct s_aux
{
	int		row_num;
	int		*col_num;
	int		max_x;
	int		max_y;
	int		max_z;
	double	***axis_data;
	double	theta;
	double	phi;
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

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		count_row_num(char *file, t_aux *aux);
int		count_col_num(char **array);
int		check_col_num(int **col_num, int row_num);
void	free_double_array(char ***array);
int		read_map(char *file, t_aux *aux);
void	init_aux(t_aux	*aux);
void	free_aux(t_aux *aux);
int		find_maximum_z(t_aux *aux);
int		find_minimum_z(t_aux *aux);

void	translate_coordinate(t_aux *aux);
void	project_coordinate(t_aux *aux, t_vector *vector);
void	calculate_normal_vector(t_aux *aux, t_vector *vector);
void	calculate_coordinate(t_aux *aux, t_vector *vector);
void	rotate_coordinate(t_aux *aux);

int		key_press(int keycode, t_mlx *mlx);

#endif