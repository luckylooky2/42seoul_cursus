/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:12 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 20:58:57 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	execute_odd_child(t_philo *philo)
{	
	int	index;

	index = check_nth_child_process(philo) + 1;
	while (philo->must_eat)
	{
		take_fork(philo, index);
		eat_dinner(philo, index);
		sleep_on_bed(philo, index);
		think_for_a_while(philo, index);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
}

void	execute_even_child(t_philo *philo)
{
	int	index;

	index = check_nth_child_process(philo) + 1;
	if (philo->is_even == EVEN)
		usleep(50 * (philo->time->philo_num / 4 + 1));
	else
		wait_time(philo, philo->time->time_eat);
	while (philo->must_eat)
	{
		take_fork(philo, index);
		eat_dinner(philo, index);
		sleep_on_bed(philo, index);
		think_for_a_while(philo, index);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
}

void	execute_last_child(t_philo *philo)
{
	int	index;

	index = check_nth_child_process(philo) + 1;
	if (philo->time->philo_num != 1)
		wait_time(philo, philo->time->time_eat * 2);
	while (philo->must_eat)
	{
		take_fork(philo, index);
		eat_dinner(philo, index);
		sleep_on_bed(philo, index);
		think_for_a_while(philo, index);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
}
