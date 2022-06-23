/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:57:55 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 21:41:02 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	take_fork(t_philo *philo, int index)
{
	sem_wait(philo->fork);
	sem_wait(philo->fork);
	print_status(philo, index, FORK);
	print_status(philo, index, FORK);
}

void	eat_dinner(t_philo *philo, int index)
{
	print_status(philo, index, EAT);
	init_check_time(philo);
	wait_time(philo, philo->time->time_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
	// if (philo->must_eat == 1)
	// 	philo->exit_status[0] += 1;
}

void	sleep_on_bed(t_philo *philo, int index)
{
	print_status(philo, index, SLEEP);
	wait_time(philo, philo->time->time_sleep);
}

void	think_for_a_while(t_philo *philo, int index)
{
	print_status(philo, index, THINK);
	if (philo->is_even == ODD
		&& philo->time->time_eat >= philo->time->time_sleep)
		wait_time(philo, philo->time->time_eat);
	else if (philo->is_even == ODD
		&& 2 * philo->time->time_eat >= philo->time->time_sleep)
		wait_time(philo, 2 * philo->time->time_eat - philo->time->time_sleep);
}