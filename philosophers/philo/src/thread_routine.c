/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:08:34 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 11:33:22 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	thread_routine_odd(t_philo *philo)
{
	while (philo->must_eat)
	{
		take_fork(philo, philo->index);
		take_fork(philo, philo->index + 1);
		eat_dinner(philo, philo->index + 1, philo->index);
		sleep_on_bed(philo);
		think_for_a_while(philo);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
}

void	thread_routine_even(t_philo *philo)
{
	int		is_last;

	if (philo->index != philo->time->philo_num)
		is_last = philo->index + 1;
	else
		is_last = 1;
	if (philo->is_even == EVEN)
		usleep(50 * (philo->time->philo_num / 4 + 1));
	else
		wait_time(philo, philo->time->time_eat);
	while (philo->must_eat)
	{
		take_fork(philo, is_last);
		take_fork(philo, philo->index);
		eat_dinner(philo, philo->index, is_last);
		sleep_on_bed(philo);
		think_for_a_while(philo);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
}

void	thread_routine_last(t_philo *philo)
{
	if (philo->time->philo_num != 1)
		wait_time(philo, philo->time->time_eat * 2);
	while (philo->must_eat)
	{
		take_fork(philo, philo->index);
		take_fork(philo, 1);
		eat_dinner(philo, 1, philo->index);
		sleep_on_bed(philo);
		think_for_a_while(philo);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
}
