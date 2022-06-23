/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:51:11 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 14:36:43 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static void	get_time(t_time *time, int flag)
{
	struct timeval	second;
	int				err_check;

	err_check = gettimeofday(&second, NULL);
	if (err_check == -1)
		exit(print_error(FAIL_GET_TIME));
	if (flag == START)
		time->start_in_ms = convert_to_millisecond(second);
	else if (flag == NOW)
		time->now_in_ms = convert_to_millisecond(second);
	else if (flag == CHECK)
		time->check_in_ms = convert_to_millisecond(second);
}

void	init_time(t_time *time)
{
	get_time(time, START);
	get_time(time, CHECK);
	time->now_in_ms = 0;
	time->check_total = 0;
	time->time_total = 0;
	time->fail = FALSE;
}

int	init_mutex(t_philo *philo)
{
	int	i;
	int	err_check;

	i = 0;
	while (i < philo->time->philo_num + 1)
	{
		err_check = pthread_mutex_init(&philo->fork[i], NULL);
		if (err_check != 0)
			return (FAIL_INIT_MUTEX);
		i++;
	}
	err_check = pthread_mutex_init(philo->print, NULL);
	if (err_check != 0)
		return (FAIL_INIT_MUTEX);
	return (SUCCESS);
}

void	init_check_time(t_philo *philo)
{
	int	idx;
	int	err_check;

	idx = philo->index;
	err_check = gettimeofday(&philo->time->check, NULL);
	if (err_check == -1)
	{
		print_error(FAIL_GET_TIME);
		philo->time->fail = TRUE;
	}
	philo->time->check_total[idx] = 0;
	// philo->time->check_in_ms[idx] = convert_to_millisecond(philo->time->check);
}
