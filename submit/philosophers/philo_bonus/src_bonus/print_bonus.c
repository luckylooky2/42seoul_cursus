/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:00:44 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/30 21:34:24 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	print_error(int err_code)
{
	if (err_code == FAIL_ARGC)
		write(STDERR_FILENO, "5 or 6 arguments are needed.\n", 29);
	else if (err_code == FAIL_PARSE_INPUT)
		write(STDERR_FILENO, "Some arguments are incorrect.\n", 30);
	else if (err_code == FAIL_GET_TIME)
		write(STDERR_FILENO, "Fail to get time.\n", 18);
	else if (err_code == FAIL_MALLOC)
		write(STDERR_FILENO, "Fail to allocate memory.\n", 25);
	else if (err_code == FAIL_OPEN_SEMAPHORE)
		write(STDERR_FILENO, "Fail to open semaphore.\n", 24);
	else if (err_code == FAIL_FORK)
		write(STDERR_FILENO, "Fail to fork child process.\n", 28);
	else if (err_code == FAIL_CREATE_THREAD)
		write(STDERR_FILENO, "Fail to create thread.\n", 23);
	else if (err_code == FAIL_DETACH_THREAD)
		write(STDERR_FILENO, "Fail to detach thread.\n", 23);
	return (err_code);
}

static void	post_semaphore(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->time->philo_num)
	{
		sem_post(philo->count);
		i++;
	}
}

void	print_status(t_philo *philo, int philo_idx, int status)
{
	sem_wait(philo->print);
	get_time(philo->time, NOW);
	philo->time->time_total = calculate_time(philo, TIME_TOTAL);
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
		post_semaphore(philo);
		unlink_semaphore();
		exit(EXIT_SUCCESS);
	}
	sem_post(philo->print);
}
