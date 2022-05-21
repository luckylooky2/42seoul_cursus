/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:09:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/21 20:51:04 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>

typedef struct s_aux
{
	int		row_num;
	int		*col_num;
	double	***axis_data;
}	t_aux;

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