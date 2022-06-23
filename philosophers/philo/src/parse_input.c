/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:53:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 21:06:30 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_bool	check_not_number(char *argv[], int i, int j)
{
	if (!(('0' <= argv[i][j] && argv[i][j] <= '9') || argv[i][j] == '+'))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	check_sign_after_number(char *argv[], int i, int j)
{
	if (('0' <= argv[i][j] && argv[i][j] <= '9') && argv[i][j + 1] == '+')
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	check_after_plus(char *argv[], int i, int j)
{
	if (argv[i][j] == '+' && !('0' <= argv[i][j + 1] && argv[i][j + 1] <= '9'))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	check_number(char *argv[])
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
			if (check_not_number(argv, i, j)
				|| check_sign_after_number(argv, i, j)
				|| check_after_plus(argv, i, j))
				return (FALSE);
			j++;
		}
		check_size_t = ft_atoi(argv[i]);
		if (check_size_t > INT_MAX)
			return (FALSE);
		i++;
	}
	return (TRUE);
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
