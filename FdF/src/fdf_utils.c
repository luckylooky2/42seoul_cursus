/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:46:20 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/27 19:08:07 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(nmemb * size);
	if (!new_str)
		return (NULL);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)new_str)[i++] = 0;
		return (new_str);
	}
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	longlong;

	i = 0;
	sign = 1;
	longlong = 0;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
		longlong = longlong * 10 + (nptr[i++] - '0');
	if (sign == -1)
		longlong *= -1;
	if (sign == 1 && (longlong < 0 || i > 19))
		return (-1);
	else if (sign == -1 && (longlong > 0 || i > 19))
		return (0);
	else
		return ((int)longlong);
}

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s[cnt])
		cnt++;
	return (cnt);
}

void	init_struct(t_aux *aux, t_vector *vector)
{
	aux->row_num = 0;
	aux->col_num = NULL;
	aux->max_x = 0;
	aux->max_y = 0;
	aux->max_z = 0;
	aux->map_data = NULL;
	aux->axis_data = NULL;
	aux->theta = 0;
	aux->phi = 0;
	aux->multi = 0;
	aux->alpha = 0;
	aux->trans_x = 0;
	aux->trans_y = 0;
	vector->a = 0;
	vector->b = 0;
	vector->c = 0;
}

void	init_data(t_aux *aux)
{
	aux->multi = 0;
	aux->alpha = 0;
	aux->trans_x = 0;
	aux->trans_y = 0;
	init_angle(aux);
}

void	free_aux(t_aux *aux)
{
	int	i;
	int	j;

	i = 0;
	while (i < aux->row_num)
	{
		j = 0;
		while (j < aux->col_num[i])
		{
			free(aux->axis_data[i][j]);
			j++;
		}
		free(aux->axis_data[i]);
		i++;
	}
	free(aux->axis_data);
	free(aux->col_num);
}

void	free_double_array(char ***array)
{
	int i;

	i = 0;
	while((*array)[i])
		free((*array)[i++]);
	free(*array);
}
