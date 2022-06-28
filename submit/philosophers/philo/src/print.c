/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:00:44 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/24 18:31:01 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	print_error(int err_code)
{
	if (err_code == FAIL_ARGC)
		write(STDERR_FILENO, "5 or 6 arguments are needed.\n", 30);
	else if (err_code == FAIL_PARSE_INPUT)
		write(STDERR_FILENO, "Some arguments are incorrect.\n", 31);
	else if (err_code == FAIL_GET_TIME)
		write(STDERR_FILENO, "Fail to get time.\n", 19);
	else if (err_code == FAIL_MALLOC)
		write(STDERR_FILENO, "Fail to allocate memory.\n", 26);
	else if (err_code == FAIL_INIT_MUTEX)
		write(STDERR_FILENO, "Fail to initialize mutex.\n", 27);
	else if (err_code == FAIL_CREATE_THREAD)
		write(STDERR_FILENO, "Fail to create thread.\n", 24);
	else if (err_code == FAIL_DETACH_THREAD)
		write(STDERR_FILENO, "Fail to detach thread.\n", 24);
	else if (err_code == FAIL_DESTROY_MUTEX)
		write(STDERR_FILENO, "Fail to destroy mutex.\n", 24);
	return (err_code);
}

int	print_status(t_philo *philo, int philo_idx, int status)
{
	int	index;

	index = philo->index;
	pthread_mutex_lock(philo->print);
	if (get_time(philo->time, NOW) == FAIL_GET_TIME)
		return (FAIL_GET_TIME);
	if (status == FORK)
		printf("%zu %d has taken a fork\n", philo->time->time_total, index);
	else if (status == EAT)
		printf("%zu %d is eatings\n", philo->time->time_total, index);
	else if (status == SLEEP)
		printf("%zu %d is sleeping\n", philo->time->time_total, index);
	else if (status == THINK)
		printf("%zu %d is thinking\n", philo->time->time_total, index);
	else if (status == DIE)
	{
		printf("%zu %d died\n", philo->time->time_total, philo_idx);
		return (EXIT);
	}
	pthread_mutex_unlock(philo->print);
	return (SUCCESS);
}
