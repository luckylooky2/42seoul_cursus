/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/24 18:52:09 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	check_nth_child_process(t_philo *philo)
{
	int	nth;

	nth = 0;
	while (nth < philo->time->philo_num)
	{
		if (philo->pid[nth] == 0)
			return (nth);
		nth++;
	}
	return (0);
}

static int	check_index(t_philo *philo, pid_t pid)
{
	int	index;

	index = 0;
	while (index < philo->time->philo_num)
	{
		if (philo->pid[index] == pid)
			return (index);
		index++;
	}
	return (0);
}

void	thread_routine_wait_semaphore_parent(t_philo *philo)
{
	sem_wait(philo->count);
}

void	execute_parent_process(t_philo *philo)
{
	pid_t	pid;
	pid_t	comp_pid;
	int		index;
	int		i;
	int		j;

	i = 0;
	j = 0;
	usleep(MILLISECOND);
	sem_wait(philo->count);
	while (i < philo->time->philo_num)
	{
		pid = 0;
		kill(philo->pid[i], SIGKILL);
		while (1)
		{
			pid = waitpid(philo->pid[j], &philo->status, WNOHANG);
			if (pid > 0)
				break ;
			j++;
			if (j == philo->time->philo_num)
				j = 0;
		}
		i++;
	}
	exit(WEXITSTATUS(philo->status));
}

int	monitor_time_die(t_philo *philo)
{
	int	index;

	index = check_nth_child_process(philo) + 1;
	get_time(philo->time, NOW);
	philo->time->check_total = calculate_time(philo, CHECK_TOTAL);
	if (philo->time->check_total >= (size_t)philo->time->time_die)
		print_status(philo, index, DIE);
	return (SUCCESS);
}

void	thread_routine_wait_semaphore(t_philo *philo)
{
	sem_wait(philo->count);
}

void	execute_child_process(t_philo *philo)
{
	int	index;
	int	err_check;

	index = check_nth_child_process(philo);
	err_check = pthread_create(&philo->thread[0], NULL, (void *)execute_odd_child, philo);
	if (err_check != 0)
		exit(print_error(FAIL_CREATE_THREAD));
	err_check = pthread_create(&philo->thread[1], NULL, (void *)thread_routine_wait_semaphore, philo);
	if (err_check != 0)
		exit(print_error(FAIL_CREATE_THREAD));
	while (monitor_time_die(philo) == SUCCESS)
		usleep(MILLISECOND / 10);
}
