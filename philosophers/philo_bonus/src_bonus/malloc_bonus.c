/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:55:03 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/27 01:20:57 by chanhyle         ###   ########.fr       */
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

static	void	open_semaphore(t_philo **philo, t_time *time)
{
	sem_t		*fork;
	sem_t		*print;
	sem_t		*count;

	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("count");
	fork = sem_open("fork", O_CREAT, 0600, time->philo_num);
	print = sem_open("print", O_CREAT, 0600, 1);
	count = sem_open("count", O_CREAT, 0600, 1);
	if (fork == SEM_FAILED || print == SEM_FAILED || count == SEM_FAILED)
		exit(print_error(FAIL_OPEN_SEMAPHORE));
	(*philo)->fork = fork;
	(*philo)->print = print;
	(*philo)->count = count;
}

void	malloc_philo(t_philo **philo, t_time *time)
{
	pid_t		*pid;
	pthread_t	*thread;

	*philo = (t_philo *)ft_calloc(sizeof(t_philo), 1);
	pid = (pid_t *)ft_calloc(sizeof(pid_t), time->philo_num + 1);
	thread = (pthread_t *)ft_calloc(sizeof(pthread_t), 2);
	if (!(*philo) || !pid || !thread)
		exit(print_error(FAIL_MALLOC));
	init_pid(pid, time->philo_num + 1);
	open_semaphore(philo, time);
	if (time->philo_num % 2)
		(*philo)->is_even = ODD;
	else
		(*philo)->is_even = EVEN;
	(*philo)->must_eat = time->must_eat;
	(*philo)->time = time;
	(*philo)->pid = pid;
	(*philo)->thread = thread;
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
