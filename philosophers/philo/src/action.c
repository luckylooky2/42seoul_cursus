/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:57:55 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 11:24:16 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_fork(t_philo *philo, int fork_index)
{
	pthread_mutex_lock(&philo->fork[fork_index]);
	print_status(philo, fork_index, FORK);
}

void	eat_dinner(t_philo *philo, int first, int second)
{
	print_status(philo, philo->index, EAT);
	init_check_time(philo);
	wait_time(philo, philo->time->time_eat);
	pthread_mutex_unlock(&philo->fork[first]);
	pthread_mutex_unlock(&philo->fork[second]);
	if (philo->must_eat == 1)
		philo->exit_status[0] += 1;
}

void	sleep_on_bed(t_philo *philo)
{
	print_status(philo, philo->index, SLEEP);
	wait_time(philo, philo->time->time_sleep);
}

void	think_for_a_while(t_philo *philo)
{
	print_status(philo, philo->index, THINK);
	if (philo->is_even == ODD
		&& philo->time->time_eat >= philo->time->time_sleep)
		wait_time(philo, philo->time->time_eat);
	else if (philo->is_even == ODD
		&& 2 * philo->time->time_eat >= philo->time->time_sleep)
		wait_time(philo, 2 * philo->time->time_eat - philo->time->time_sleep);
}
