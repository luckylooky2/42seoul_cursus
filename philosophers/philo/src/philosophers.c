/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:42:59 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/16 22:14:01 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_philo *philo, int philo_idx, int status)
{
	int	index;
	
	index = philo->index;
	if (status == FORK)
		printf("%zu %d has taken a fork %d\n", philo->time->time_total, index, philo_idx);
	else if (status == EAT)
		printf("%zu %d is eatings\n", philo->time->time_total, index);
	else if (status == SLEEP)
		printf("%zu %d is sleeping\n", philo->time->time_total, index);
	else if (status == THINK)
		printf("%zu %d is thinking\n", philo->time->time_total,  index);
	else if (status == DIE)
	{
		printf("%zu %d died\n", philo->time->time_total,  index);
		exit(1);
	}
}

int	print_time(t_philo *philo, int philo_idx, int status)
{
	int	err_check;
	
	err_check = gettimeofday(&philo->time->now, NULL);
	if (err_check == -1)
		return (FAIL_GET_TIME);
	if (status == EAT)
	{
		err_check = gettimeofday(&philo->time->check, NULL);
		if (err_check == -1)
			return (FAIL_GET_TIME);
		philo->time->check_total = 0;
	}
	philo->time->now_in_ms = (philo->time->now.tv_sec * 1000) + (philo->time->now.tv_usec / 1000);
	philo->time->time_total = philo->time->now_in_ms - philo->time->start_in_ms;
	philo->time->check_in_ms = (philo->time->check.tv_sec * 1000) + (philo->time->check.tv_usec / 1000);
	philo->time->check_total = philo->time->now_in_ms - philo->time->check_in_ms;
	print_status(philo, philo_idx, status);
	return (1);
}

int	thread_routine_odd(void *arg)
{
	t_philo *philo;
	int		philo_idx;
	int		eat;
	
	philo = (t_philo *)arg;
	philo_idx = philo->index;
	eat = philo->time->must_eat;
	usleep(50);
	while (eat)
	{
		pthread_mutex_lock(&philo->fork[philo_idx]);
		print_time(philo, philo_idx, FORK);
		pthread_mutex_lock(&philo->fork[philo_idx + 1]);
		print_time(philo, philo_idx + 1, FORK);
		print_time(philo, philo_idx, EAT);
		usleep(philo->time->time_eat * MILLISECOND);
		pthread_mutex_unlock(&philo->fork[philo_idx + 1]);
		pthread_mutex_unlock(&philo->fork[philo_idx]);
		print_time(philo, philo_idx, SLEEP);
		usleep(philo->time->time_sleep * MILLISECOND);
		print_time(philo, philo_idx, THINK);
		if (eat > 0)
			eat--;
	}
	return (SUCCESS);
}

int	thread_routine_even(void *arg)
{
	t_philo *philo;
	int		philo_idx;
	int		is_last;
	int		eat;
	
	philo = (t_philo *)arg;
	philo_idx = philo->index;
	eat = philo->time->must_eat;
	if (philo_idx != philo->time->philo_num)
		is_last = philo_idx + 1;
	else
		is_last = 1;
	while (eat)
	{
		pthread_mutex_lock(&philo->fork[is_last]);
		print_time(philo, is_last, FORK);
		pthread_mutex_lock(&philo->fork[philo_idx]);
		print_time(philo, philo_idx, FORK);
		print_time(philo, philo_idx, EAT);
		usleep(philo->time->time_eat * MILLISECOND);
		pthread_mutex_unlock(&philo->fork[philo_idx]);
		if (philo_idx != philo->time->philo_num)
			pthread_mutex_unlock(&philo->fork[philo_idx + 1]);
		else
			pthread_mutex_unlock(&philo->fork[1]);
		print_time(philo, philo_idx, SLEEP);
		usleep(philo->time->time_sleep * MILLISECOND);
		print_time(philo, philo_idx, THINK);
		if (eat > 0)
			eat--;
	}
	return (SUCCESS);
}

int	init_data(t_philo **philo, t_time *time)
{
	pthread_t 		*thread;
	pthread_mutex_t	*fork;
	size_t			philo_num;
	int				i;

	i = 0;
	philo_num = time->philo_num;
	*philo = (t_philo *)ft_calloc(sizeof(t_philo), philo_num);
	thread = (pthread_t *)ft_calloc(sizeof(pthread_t), philo_num);
	fork = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t)
			, philo_num + 1);
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

int	init_time(t_time *time)
{
	int	err_check;

	err_check = gettimeofday(&time->start, NULL);
	if (err_check == -1)
		return (FAIL_GET_TIME);
	time->start_in_ms = (time->start.tv_sec * 1000) + (time->start.tv_usec / 1000);
	time->check_in_ms = 0;
	time->now_in_ms = 0;
	time->time_total = 0;
	time->check_total = 0;
	return (SUCCESS);
}

static int	check_number(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(('0' <= argv[i][j] && argv[i][j] <= '9') || 
				argv[i][j] == '+') || (('0' <= argv[i][j] && argv[i][j] <= '9')
				&& argv[i][j + 1] == '+') || (argv[i][j] == '+' && 
				!('0' <= argv[i][j + 1] && argv[i][j + 1] <= '9')))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_input(int argc, char *argv[], t_time *time)
{
	if (check_number(argv) == 0)
		return (FAIL_PARSE_INPUT);
	time->philo_num = ft_atoull(argv[1]);
	time->time_die = ft_atoull(argv[2]);
	time->time_eat = ft_atoull(argv[3]);
	time->time_sleep = ft_atoull(argv[4]);
	time->must_eat = ft_atoull(argv[5]);
	if (time->must_eat == 0)
		time->must_eat = INT_MIN;
	if (time->philo_num == SIZE_T_MAX || time->time_die == SIZE_T_MAX
		|| time->time_eat == SIZE_T_MAX || time->time_sleep == SIZE_T_MAX 
		|| time->must_eat == SIZE_T_MAX)
		return (FAIL_PARSE_INPUT);
	return (SUCCESS);
}

int	put_error(int err_code)
{
	if (err_code == FAIL_ARGC)
		write(STDIN_FILENO, "5 or 6 arguments are needed.\n", 30);
	else if (err_code == FAIL_PARSE_INPUT)
		write(STDIN_FILENO, "Some arguments are incorrect.\n", 31);
	else if (err_code == FAIL_GET_TIME)
		write(STDIN_FILENO, "Fail to get time.\n", 19);
	else if (err_code == FAIL_MALLOC)
		write(STDIN_FILENO, "Fail to allocate memory.\n", 26);
	return (err_code);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_time	time;
	int 	i = -1;

	if (argc != 5 && argc != 6)
		return (put_error(FAIL_ARGC));
	if (parse_input(argc, argv, &time))
		return (put_error(FAIL_PARSE_INPUT));
	if (init_time(&time))
		return (put_error(FAIL_GET_TIME));
	if (init_data(&philo, &time))
		return (put_error(FAIL_MALLOC));
	while (++i < philo->time->philo_num + 1)
		pthread_mutex_init(&philo->fork[i], NULL);
	i = -1;
	while (++i < philo->time->philo_num)
	{
		if (i % 2 == 0)
			pthread_create(&(philo->thread[i]), NULL, (void *)thread_routine_odd, (void *)(philo + i));
		else
			pthread_create(&(philo->thread[i]), NULL, (void *)thread_routine_even, (void *)(philo + i));
	}
	i = -1;
	while (++i < philo->time->philo_num)
		pthread_join(philo->thread[i], NULL);
	return (SUCCESS);
}