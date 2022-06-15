/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:42:59 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/15 22:23:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*thread_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	// printf("i : %d\n", philo->time->start_in_ms);
	return (NULL);
}

int	init_data(t_philo **philo, t_time *time, size_t philo_num)
{
	pthread_t 		*thread;
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	*philo = (t_philo *)ft_calloc(sizeof(t_philo), philo_num);
	thread = (pthread_t *)ft_calloc(sizeof(pthread_t), philo_num);
	fork = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), philo_num);
	if (!(*philo) || !thread || !fork )
		return (FAIL_MALLOC);
	while (i < philo_num)
	{
		(*philo + i)->index = i + 1;
		(*philo + i)->time = time;
		(*philo + i)->thread = thread;
		(*philo + i)->fork = fork;
		i++;
	}
	return (SUCCESS);
}

int	parse_input(int argc, char *argv[], size_t *philo_num, t_time *time)
{
	*philo_num = ft_atoll(argv[1]);
	printf("1 : %zu\n", *philo_num);
	time->time_die = ft_atoll(argv[2]);
	printf("2 : %zu\n", time->time_die);
	time->time_eat = ft_atoll(argv[3]);
	printf("3 : %zu\n", time->time_eat);
	time->time_sleep = ft_atoll(argv[4]);
	printf("4 : %zu\n", time->time_sleep);
	time->must_eat = ft_atoll(argv[5]);
	printf("5 : %zu\n", time->must_eat);
	time->err_check = gettimeofday(&time->start, NULL);
	if (time->err_check == -1)
		return (FAIL_TIME);
	time->start_in_ms = (time->start.tv_sec * 1000) + (time->start.tv_usec / 1000);
	time->now_in_ms = 0;
	time->time_total = 0;
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_time	time;
	size_t	philo_num;
	int 	i = -1;

	if (argc != 5 && argc != 6)
		return (FAIL_ARGC);
	if (parse_input(argc, argv, &philo_num, &time))
		return (FAIL_TIME);
	if (init_data(&philo, &time, philo_num))
		return (FAIL_MALLOC);
	pthread_mutex_init(philo->fork, NULL);
	while (++i < philo_num)
		pthread_create(&(philo->thread[i]), NULL, (void *)thread_routine, (void *)(philo + i));
	i = -1;
	while (++i < philo_num)
		pthread_join(philo->thread[i], NULL);
	return (SUCCESS);
}