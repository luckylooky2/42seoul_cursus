/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/01 13:37:54 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static void	terminate_child_process(t_philo *philo)
{
	pid_t	pid;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < philo->time->philo_num)
	{
		pid = 0;
		kill(philo->pid[i], SIGKILL);
		while (1)
		{
			if (j == philo->time->philo_num)
				j = 0;
			pid = waitpid(philo->pid[j], &philo->status, WNOHANG);
			if (pid > 0)
				break ;
			j++;
		}
		i++;
	}
}

static void	detach_thread(t_philo *philo)
{
	int	i;
	int	err_check;

	i = 0;
	while (i < 2)
	{
		err_check = pthread_detach(philo->thread[i]);
		if (err_check != 0)
			exit(print_error(FAIL_DETACH_THREAD));
		i++;
	}
}

void	execute_parent_process(t_philo *philo)
{
	usleep(MILLISECOND);
	sem_wait(philo->count);
	terminate_child_process(philo);
	unlink_semaphore();
	exit(philo->status);
}

void	execute_child_process(t_philo *philo)
{
	int	err_check;

	err_check = pthread_create(&philo->thread[0], NULL,
			(void *)thread_routine_child_process, philo);
	if (err_check != 0)
		exit(print_error(FAIL_CREATE_THREAD));
	err_check = pthread_create(&philo->thread[1], NULL,
			(void *)thread_routine_wait_semaphore, philo);
	if (err_check != 0)
		exit(print_error(FAIL_CREATE_THREAD));
	detach_thread(philo);
	while (monitor_time_die(philo) == SUCCESS)
		usleep(MILLISECOND / 10);
}
