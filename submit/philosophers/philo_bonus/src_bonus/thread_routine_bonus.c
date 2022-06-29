/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:12 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/29 16:24:15 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	thread_routine_child_process(t_philo *philo)
{	
	int	index;

	index = check_nth_child_process(philo) + 1;
	while (philo->must_eat)
	{
		take_fork(philo, index);
		eat_dinner(philo, index);
		sleep_on_bed(philo, index);
		think_for_a_while(philo, index);
	}
	while (1)
		;
}

void	thread_routine_wait_semaphore(t_philo *philo)
{
	sem_wait(philo->count);
}
