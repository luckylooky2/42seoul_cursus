/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 22:15:45 by chanhyle         ###   ########.fr       */
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

void	execute_parent_process(t_philo *philo)
{
	pid_t	pid;
	pid_t	comp_pid;
	int		i;

	i = 0;
	pid = wait(&philo->status);
	while (i < philo->time->philo_num)
	{
		kill(philo->pid[i], SIGKILL);
		i++;
	}
	exit(WEXITSTATUS(philo->status));
}

int	monitor_time_die(t_philo *philo)
{
	int				err_check;
	int				index;
	struct timeval	now;

	err_check = gettimeofday(&now, NULL);
	index = check_nth_child_process(philo) + 1;
	if (err_check == -1)
		exit(print_error(FAIL_GET_TIME));
	philo->time->now_in_ms = convert_to_millisecond(now);
	philo->time->time_total = calculate_time(philo, TIME_TOTAL);
	philo->time->check_total = calculate_time(philo, CHECK_TOTAL);
	if (philo->time->check_total >= (size_t)philo->time->time_die)
		print_status(philo, index, DIE);
	// if (philo->exit_status[0] == philo->time->philo_num
	// 	|| philo->time->fail == TRUE)
	// 	return (lock_mutex(philo)); 
	return (SUCCESS);
}

void	execute_child_process(t_philo *philo)
{
	int	index;
	int	err_check;
	pthread_t th;

	index = check_nth_child_process(philo);
	err_check = pthread_create(philo->thread, NULL, (void *)execute_odd_child, philo);
	// if (philo->is_even == ODD && !(index % 2) && index + 1 == philo->time->philo_num)
	// 	err_check = pthread_create(philo->thread, NULL, (void *)execute_last_child, philo);
	// else if (!(index % 2))
	// 	err_check = pthread_create(philo->thread, NULL, (void *)execute_odd_child, philo);
	// else if (index % 2)
	// 	err_check = pthread_create(philo->thread, NULL, (void *)execute_even_child, philo);
	if (err_check != 0)
		exit(print_error(FAIL_CREATE_THREAD));
	while (monitor_time_die(philo) == SUCCESS)
		usleep(MILLISECOND / 10);
	while (1) ;
}
