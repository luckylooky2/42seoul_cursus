/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:09:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/23 22:16:42 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

typedef struct s_aux
{
	int		row_num;
	int		*col_num;
	double	***axis_data;
}	t_aux;

typedef struct s_angle
{
	double	theta;
	double	phi;
}	t_angle;

typedef struct s_vector
{
	double	a;
	double	b;
	double	c;
}	t_vector;

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
int		find_max_z(t_aux *aux);
int		find_min_z(t_aux *aux);
void	translate_coordinate(t_aux *aux);
void	transform_coordinate(t_aux *aux, t_angle *angle, t_vector *vector);
void	calculate_normal_vector(t_angle *a, t_vector *vec, int theta, int phi);
void	calculate_coordinate(double ***axis, t_vector *vec, int row, int *col);
