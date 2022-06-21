/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:51:11 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/21 17:05:02 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_time(t_time *time)
{
	int	err_check;

	err_check = gettimeofday(&time->start, NULL);
	if (err_check == -1)
		return (FAIL_GET_TIME);
	time->start_in_ms = convert_to_millisecond(time->start);
	time->now_in_ms = 0;
	time->time_total = 0;
	time->start.tv_sec = 0;
	time->start.tv_usec = 0;
	time->now.tv_sec = 0;
	time->now.tv_usec = 0;
	time->check.tv_sec = 0;
	time->check.tv_usec = 0;
	time->check_in_ms = NULL;
	time->check_total = NULL;
	time->fail = FALSE;
	return (SUCCESS);
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
	philo->time->check_in_ms[idx] = convert_to_millisecond(philo->time->check);
}
