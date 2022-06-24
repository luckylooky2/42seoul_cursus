/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:55:03 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/24 15:30:46 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static void	init_pid(pid_t	*pid, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pid[i] = 1;
		i++;
	}
}

void	malloc_thread(t_philo **philo, t_time *time)
{
	pid_t		*pid;
	sem_t		*fork;
	pthread_t	*thread;
	sem_t		*print;
	sem_t		*exit_status;

	*philo = (t_philo *)ft_calloc(sizeof(t_philo), 1);
	pid = (pid_t *)ft_calloc(sizeof(pid_t), time->philo_num + 1);
	thread = (pthread_t *)ft_calloc(sizeof(pthread_t), 1);
	if (!(*philo) || !pid || !thread)
		exit(print_error(FAIL_MALLOC));
	init_pid(pid, time->philo_num + 1);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("exit_status");
	fork = sem_open("fork", O_CREAT, 0600, time->philo_num);
	print = sem_open("print", O_CREAT, 0600, 1);
	exit_status = sem_open("exit_status", O_CREAT, 0600, 1);
	if (fork == SEM_FAILED || print == SEM_FAILED || exit_status == SEM_FAILED)
		exit(print_error(FAIL_SEMAPHORE));
	if (time->philo_num % 2)
		(*philo)->is_even = ODD;
	else
		(*philo)->is_even = EVEN;
	(*philo)->must_eat = time->must_eat;
	(*philo)->time = time;
	(*philo)->pid = pid;
	(*philo)->fork = fork;
	(*philo)->thread = thread;
	(*philo)->print = print;
	(*philo)->exit_status = exit_status;
	(*philo)->status = 0;

}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(nmemb * size);
	if (!new_str)
		return (NULL);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)new_str)[i++] = 0;
		return (new_str);
	}
}
