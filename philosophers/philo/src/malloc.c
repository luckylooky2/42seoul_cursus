/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:55:03 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/21 19:20:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	malloc_time(t_time *time)
{	
	size_t	*check_in_ms;
	size_t	*check_total;
	int		philo_num;
	int		err_check;
	int		i;

	i = -1;
	philo_num = time->philo_num;
	err_check = gettimeofday(&time->check, NULL);
	if (err_check == -1)
		return (FAIL_GET_TIME);
	check_in_ms = (size_t *)ft_calloc(sizeof(size_t), philo_num + 1);
	check_total = (size_t *)ft_calloc(sizeof(size_t), philo_num + 1);
	if (!check_in_ms || !check_total)
		return (FAIL_MALLOC);
	while (++i < philo_num + 1)
		check_in_ms[i] = convert_to_millisecond(time->check);
	i = -1;
	while (++i < philo_num)
	{	
		time->check_in_ms = check_in_ms;
		time->check_total = check_total;
	}
	return (SUCCESS);
}

static void	allocate_individual_source(t_philo **philo, t_time *time, int i)
{
	if (time->philo_num % 2)
		(*philo + i)->is_even = ODD;
	else
		(*philo + i)->is_even = EVEN;
	(*philo + i)->index = i + 1;
	(*philo + i)->must_eat = time->must_eat;
}

int	malloc_thread(t_philo **philo, t_time *time)
{
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	int				*exit_status;
	int				i;

	i = -1;
	*philo = (t_philo *)ft_calloc(sizeof(t_philo), time->philo_num);
	thread = (pthread_t *)ft_calloc(sizeof(pthread_t), time->philo_num);
	fork = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t),
			time->philo_num + 1);
	print = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), 1);
	exit_status = (int *)ft_calloc(sizeof(int), time->philo_num + 1);
	if (!(*philo) || !thread || !fork || !print || !exit_status)
		return (FAIL_MALLOC);
	while (++i < time->philo_num)
	{
		allocate_individual_source(philo, time, i);
		(*philo + i)->time = time;
		(*philo + i)->thread = thread;
		(*philo + i)->fork = fork;
		(*philo + i)->print = print;
		(*philo + i)->exit_status = exit_status;
	}
	return (SUCCESS);
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
