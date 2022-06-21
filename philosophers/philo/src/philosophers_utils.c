/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:39:06 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/21 19:06:20 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t	convert_to_millisecond(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

size_t	calculate_time(t_philo *philo, int index, int flag)
{
	if (flag == TIME_TOTAL)
		return (philo->time->now_in_ms - philo->time->start_in_ms);
	else
		return (philo->time->now_in_ms - philo->time->check_in_ms[index]);
}

static size_t	get_now(t_philo *philo)
{
	struct timeval	now;
	int				err_check;

	err_check = gettimeofday(&now, NULL);
	if (err_check == -1)
	{
		print_error(FAIL_GET_TIME);
		philo->time->fail = TRUE;
		return (FAIL_GET_TIME);
	}
	return (convert_to_millisecond(now));
}

void	wait_time(t_philo *philo, unsigned int time_wait)
{
	size_t	target;

	target = time_wait + get_now(philo);
	while (target > get_now(philo))
		usleep(MILLISECOND / 2);
}
