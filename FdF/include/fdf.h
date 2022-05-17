/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:09:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/17 22:10:32 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>

typedef struct s_data
{
	double	x;
	double	y;
	double	z;
	double	t;
}	t_data;

typedef struct s_aux
{
	char	**lines;
	int		**map;
	int		*col_ary;
	t_data	***data;
}	t_aux;

int		ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c)