/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:09:58 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/24 13:12:28 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	lock_mutex(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	return (EXIT);
}

int	monitor_time_die(t_philo *philo)
{
	int	i;
	int	err_check;

	i = 1;
	err_check = gettimeofday(&philo->time->now, NULL);
	if (err_check == -1)
	{
		print_error(FAIL_GET_TIME);
		return (EXIT);
	}
	philo->time->now_in_ms = convert_to_millisecond(philo->time->now);
	philo->time->time_total = calculate_time(philo, 0, TIME_TOTAL);
	while (i < philo->time->philo_num + 1)
	{
		philo->time->check_total[i] = calculate_time(philo, i, CHECK_TOTAL);
		if (philo->time->check_total[i] >= (size_t)philo->time->time_die)
			return (print_status(philo, i, DIE));
		if (philo->exit_status[0] == philo->time->philo_num
			|| philo->time->fail == TRUE)
			return (lock_mutex(philo));
		i++;
	}
	return (SUCCESS);
}
