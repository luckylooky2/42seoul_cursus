/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:39:06 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/27 01:27:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

size_t	convert_to_millisecond(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

size_t	calculate_time(t_philo *philo, int flag)
{
	if (flag == TIME_TOTAL)
		return (philo->time->now_in_ms - philo->time->start_in_ms);
	else
		return (philo->time->now_in_ms - philo->time->check_in_ms);
}

static size_t	get_now(t_philo *philo)
{
	struct timeval	now;
	int				err_check;

	err_check = gettimeofday(&now, NULL);
	if (err_check == -1)
		exit(print_error(FAIL_GET_TIME));
	return (convert_to_millisecond(now));
}

void	wait_time(t_philo *philo, unsigned int time_wait)
{
	size_t	target;

	target = time_wait + get_now(philo);
	while (target > get_now(philo))
		usleep(MILLISECOND / 2);
}

t_bool	check_child_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->time->philo_num)
	{
		if (philo->pid[i] == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
