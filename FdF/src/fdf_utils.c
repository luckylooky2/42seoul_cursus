/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:46:20 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/21 22:50:24 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

void	init_aux(t_aux	*aux)
{
	aux->row_num = 0;
	aux->col_num = NULL;
	aux->axis_data = NULL;
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