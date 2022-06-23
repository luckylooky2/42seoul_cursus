/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:00:44 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 22:03:35 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

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
	else if (err_code == FAIL_SEMAPHORE)
		write(STDERR_FILENO, "Fail to make semaphore.\n", 25);
	else if (err_code == FAIL_INIT_MUTEX)
		write(STDERR_FILENO, "Fail to initiate mutex.\n", 25);
	else if (err_code == FAIL_CREATE_THREAD)
		write(STDERR_FILENO, "Fail to create thread.\n", 24);
	else if (err_code == FAIL_DETACH_THREAD)
		write(STDERR_FILENO, "Fail to detach thread.\n", 24);
	else if (err_code == FAIL_DESTROY_MUTEX)
		write(STDERR_FILENO, "Fail to destroy mutex.\n", 24);
	return (err_code);
}

void	print_status(t_philo *philo, int philo_idx, int status)
{
	int i = 0;
	sem_wait(philo->print);
	if (status == FORK)
		printf("%zu %d has taken a fork\n", philo->time->time_total, philo_idx);
	else if (status == EAT)
		printf("%zu %d is eatings\n", philo->time->time_total, philo_idx);
	else if (status == SLEEP)
		printf("%zu %d is sleeping\n", philo->time->time_total, philo_idx);
	else if (status == THINK)
		printf("%zu %d is thinking\n", philo->time->time_total, philo_idx);
	else if (status == DIE)
	{
		printf("%zu %d died\n", philo->time->time_total, philo_idx);
		exit(EXIT);
	}
	sem_post(philo->print);
}
