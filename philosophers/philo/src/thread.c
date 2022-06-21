/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:05:59 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/21 19:07:47 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_thread(t_philo *philo)
{
	int	i;
	int	err_check;

	i = 0;
	while (i < philo->time->philo_num)
	{
		if (philo->is_even == ODD && !(i % 2)
			&& i + 1 == philo->time->philo_num)
			err_check = pthread_create(&(philo->thread[i]), NULL,
					(void *)thread_routine_last, (philo + i));
		else if (!(i % 2))
			err_check = pthread_create(&(philo->thread[i]), NULL,
					(void *)thread_routine_odd, (philo + i));
		else if (i % 2)
			err_check = pthread_create(&(philo->thread[i]), NULL,
					(void *)thread_routine_even, (philo + i));
		if (err_check != 0)
			return (FAIL_CREATE_THREAD);
		i++;
	}
	return (SUCCESS);
}

int	detach_thread(t_philo *philo)
{
	int	i;
	int	err_check;

	i = 0;
	while (++i < philo->time->philo_num)
	{
		err_check = pthread_detach(philo->thread[i]);
		if (err_check != 0)
			return (FAIL_DETACH_THREAD);
		i++;
	}
	return (SUCCESS);
}

int	destroy_mutex(t_philo *philo)
{
	int	i;
	int	err_check;

	i = 0;
	while (i < philo->time->philo_num + 1)
	{
		pthread_mutex_unlock(&philo->fork[i]);
		err_check = pthread_mutex_destroy(&philo->fork[i]);
		if (err_check != 0)
			return (FAIL_DESTROY_MUTEX);
		i++;
	}
	pthread_mutex_unlock(philo->print);
	err_check = pthread_mutex_destroy(philo->print);
	if (err_check != 0)
		return (FAIL_DESTROY_MUTEX);
	return (SUCCESS);
}
