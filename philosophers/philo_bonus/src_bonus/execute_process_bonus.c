/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/24 14:29:42 by chanhyle         ###   ########.fr       */
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

void	execute_parent_process(t_philo *philo)
{
	pid_t	pid;
	pid_t	comp_pid;
	int		index;
	int		i;

	i = 0;
	pid = wait(&philo->status);
	index = check_index(philo, pid);
	while (i < philo->time->philo_num)
	{
		if (index != i)
		{
			kill(philo->pid[i], SIGKILL);
			pid = waitpid(philo->pid[i], &philo->status, 0);
		}
		i++;
	}
	exit(WEXITSTATUS(philo->status));
}

static size_t	calculate_must_eat_time(t_philo *philo)
{
	int	time_eat;
	int	must_eat;
	int	philo_num;

	time_eat = philo->time->time_eat;
	must_eat = philo->time->must_eat;
	philo_num = philo->time->philo_num;
	return (time_eat * must_eat * (philo_num % 2 + 2) + 1);
}

int	monitor_time_die(t_philo *philo)
{
	int				err_check;
	int				index;
	size_t			must_eat_time;
	struct timeval	now;

	index = check_nth_child_process(philo) + 1;
	must_eat_time = calculate_must_eat_time(philo);
	err_check = gettimeofday(&now, NULL);
	if (err_check == -1)
		exit(print_error(FAIL_GET_TIME));
	philo->time->now_in_ms = convert_to_millisecond(now);
	philo->time->time_total = calculate_time(philo, TIME_TOTAL);
	philo->time->check_total = calculate_time(philo, CHECK_TOTAL);
	if (philo->time->check_total >= (size_t)philo->time->time_die)
		print_status(philo, index, DIE);
	if (philo->time->time_total > must_eat_time)
		exit(EXIT_MUST_EAT);
	return (SUCCESS);
}

void	execute_child_process(t_philo *philo)
{
	int	index;
	int	err_check;

	index = check_nth_child_process(philo);
	err_check = pthread_create(philo->thread, NULL, (void *)execute_odd_child, philo);
	if (err_check != 0)
		exit(print_error(FAIL_CREATE_THREAD));
	while (monitor_time_die(philo) == SUCCESS)
		usleep(MILLISECOND / 10);
}
