/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:53:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/21 19:19:58 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_number(char *argv[])
{
	int		i;
	int		j;
	size_t	check_size_t;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(('0' <= argv[i][j] && argv[i][j] <= '9')
				|| argv[i][j] == '+') || (('0' <= argv[i][j]
				&& argv[i][j] <= '9') && argv[i][j + 1] == '+')
				|| (argv[i][j] == '+' && !('0' <= argv[i][j + 1]
				&& argv[i][j + 1] <= '9')))
				return (0);
			j++;
		}
		check_size_t = ft_atoi(argv[i]);
		if (check_size_t > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	parse_input(char *argv[], t_time *time)
{
	if (check_number(argv) == 0)
		return (FAIL_PARSE_INPUT);
	time->philo_num = ft_atoi(argv[1]);
	time->time_die = ft_atoi(argv[2]);
	time->time_eat = ft_atoi(argv[3]);
	time->time_sleep = ft_atoi(argv[4]);
	time->must_eat = ft_atoi(argv[5]);
	if (!time->philo_num || !time->time_die
		|| !time->time_eat || !time->time_sleep)
		return (FAIL_PARSE_INPUT);
	if (time->must_eat == 0)
		time->must_eat = -1;
	return (SUCCESS);
}

long long	ft_atoi(const char *nptr)
{
	int			i;
	long long	longlong;

	i = 0;
	longlong = 0;
	if (!nptr)
		return (0);
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] == '0')
		i++;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		longlong = longlong * 10 + (nptr[i] - '0');
		if ((longlong == INT_MAX / 10) && nptr[i + 1] > ('0' + INT_MAX % 10))
			return (OVER_INT_MAX);
		else if (longlong > INT_MAX / 10
			&& ('0' <= nptr[i + 1] && nptr[i + 1] <= '9'))
			return (OVER_INT_MAX);
		i++;
	}
	return ((int)longlong);
}

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	if (s == NULL)
		return (0);
	while (s[cnt])
		cnt++;
	return (cnt);
}
