/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:42:59 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/20 15:14:40 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t get_now(void)
{
	struct	timeval now;
	int		err_check;

	err_check = gettimeofday(&now, NULL);
	if (err_check == -1)
		return (0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	wait_time(unsigned int time_wait)
{
	size_t	target;
	
	target = time_wait + get_now();
	while (target > get_now())
		usleep(MILLISECOND / 2);
}

void	print_status(t_philo *philo, int philo_idx, int status)
{
	int	index;
	
	index = philo->index;
	if (status == FORK)
		printf("%zu %d has taken a fork\n", philo->time->time_total, index);
	else if (status == EAT)
		printf("%zu %d is eatings\n", philo->time->time_total, index);
	else if (status == SLEEP)
		printf("%zu %d is sleeping\n", philo->time->time_total, index);
	else if (status == THINK)
		printf("%zu %d is thinking\n", philo->time->time_total,  index);
	else if (status == DIE)
	{
		printf("%zu %d died\n", philo->time->time_total, philo_idx);
		exit(1);
	}
}

int	print_time(t_philo *philo, int philo_idx, int status)
{
	int	idx;
	int	err_check;

	idx = philo->index;
	if (status == EAT)
	{
		err_check = gettimeofday(&philo->time->check, NULL); // 기준 시간 받아오기
		if (err_check == -1)
			return (FAIL_GET_TIME);
		philo->time->check_total[idx] = 0; // 기준 시간 초기화
		philo->time->check_in_ms[idx] = (philo->time->check.tv_sec * 1000) + (philo->time->check.tv_usec / 1000); // 기준 시간 체크
	}
	print_status(philo, philo_idx, status);
	return (1);
}

int	thread_routine_odd(t_philo *philo)
{
	int		is_last;

	if (philo->index != philo->time->philo_num)
		is_last = philo->index + 1;
	else
		is_last = 1;
	if (philo->is_even == EVEN)
		usleep(50 * (philo->time->philo_num / 4 + 1));
	else
		wait_time(philo->time->time_eat);
	while (philo->must_eat)
	{
		pthread_mutex_lock(&philo->fork[philo->index]);
		print_time(philo, philo->index, FORK);
		pthread_mutex_lock(&philo->fork[is_last]);
		print_time(philo, is_last, FORK);
		print_time(philo, philo->index, EAT);
		wait_time(philo->time->time_eat);
		pthread_mutex_unlock(&philo->fork[is_last]);
		pthread_mutex_unlock(&philo->fork[philo->index]);
		print_time(philo, philo->index, SLEEP);
		wait_time(philo->time->time_sleep);
		print_time(philo, philo->index, THINK);
		if (philo->is_even == ODD && philo->time->time_eat >= philo->time->time_sleep)
			wait_time(philo->time->time_eat);
		else if (philo->is_even == ODD && 2 * philo->time->time_eat >= philo->time->time_sleep)
			wait_time(2 * philo->time->time_eat - philo->time->time_sleep);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
	philo->time->exit_status = 1;
	return (SUCCESS);
}

int	thread_routine_last(t_philo *philo)
{
	wait_time(philo->time->time_eat * 2);
	while (philo->must_eat)
	{
		pthread_mutex_lock(&philo->fork[philo->index]);
		print_time(philo, philo->index, FORK);
		pthread_mutex_lock(&philo->fork[1]);
		print_time(philo, 1, FORK);
		print_time(philo, philo->index, EAT);
		wait_time(philo->time->time_eat);
		pthread_mutex_unlock(&philo->fork[1]);
		pthread_mutex_unlock(&philo->fork[philo->index]);
		print_time(philo, philo->index, SLEEP);
		wait_time(philo->time->time_sleep);
		print_time(philo, philo->index, THINK);
		if (philo->time->time_eat >= philo->time->time_sleep)
			wait_time(philo->time->time_eat);
		else if (2 * philo->time->time_eat >= philo->time->time_sleep)
			wait_time(2 * philo->time->time_eat - philo->time->time_sleep);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
	philo->time->exit_status = 1;
	return (SUCCESS);
}

int	thread_routine_even(t_philo *philo)
{
	int		is_last;
	
	if (philo->index != philo->time->philo_num)
		is_last = philo->index + 1;
	else
		is_last = 1;
	while (philo->must_eat)
	{
		pthread_mutex_lock(&philo->fork[is_last]);
		print_time(philo, is_last, FORK);
		pthread_mutex_lock(&philo->fork[philo->index]);
		print_time(philo, philo->index, FORK);
		print_time(philo, philo->index, EAT);
		wait_time(philo->time->time_eat);
		pthread_mutex_unlock(&philo->fork[philo->index]);
		pthread_mutex_unlock(&philo->fork[is_last]);
		print_time(philo, philo->index, SLEEP);
		wait_time(philo->time->time_sleep);
		print_time(philo, philo->index, THINK);
		if (philo->is_even == ODD && philo->time->time_eat >= philo->time->time_sleep)
			wait_time(philo->time->time_eat);
		else if (philo->is_even == ODD && 2 * philo->time->time_eat >= philo->time->time_sleep)
			wait_time(2 * philo->time->time_eat - philo->time->time_sleep);
		if (philo->must_eat > 0)
			philo->must_eat--;
	}
	philo->time->exit_status = 1;
	return (SUCCESS);
}

int	malloc_time(t_time *time)
{	
	size_t	*check_in_ms;
	size_t	*check_total;
	size_t	philo_num;
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
	{
		check_total[i] = 0;
		check_in_ms[i] = (time->check.tv_sec * 1000) + (time->check.tv_usec / 1000);
	}
	i = -1;
	while (++i < philo_num)
	{	
		time->check_in_ms = check_in_ms;
		time->check_total = check_total;
	}
	return (SUCCESS);
}

int	malloc_thread(t_philo **philo, t_time *time)
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
	if (!(*philo) || !thread || !fork)
		return (FAIL_MALLOC);
	while (i < philo_num)
	{
		if (philo_num % 2)
			(*philo + i)->is_even = ODD;
		else
			(*philo + i)->is_even = EVEN;
		(*philo + i)->index = i + 1;
		(*philo + i)->must_eat = time->must_eat;
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
	time->now_in_ms = 0;
	time->time_total = 0;
	time->exit_status = 0;
	time->start.tv_sec = 0;
	time->start.tv_usec = 0;
	time->now.tv_sec = 0;
	time->now.tv_usec = 0;
	time->check.tv_sec = 0;
	time->check.tv_usec = 0;
	time->check_in_ms = NULL;
	time->check_total = NULL;
	return (SUCCESS);
}

static int	check_number(char *argv[])
{
	int		i;
	int		j;
	size_t	check_size_t;

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
		check_size_t = ft_atoi(argv[i]);
		if (check_size_t > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	parse_input(int argc, char *argv[], t_time *time)
{
	if (check_number(argv) == 0)
		return (FAIL_PARSE_INPUT);
	time->philo_num = ft_atoi(argv[1]);
	time->time_die = ft_atoi(argv[2]);
	time->time_eat = ft_atoi(argv[3]);
	time->time_sleep = ft_atoi(argv[4]);
	time->must_eat = ft_atoi(argv[5]);
	if (time->must_eat == 0)
		time->must_eat = -1;
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

int	check_time_die(t_philo *philo)
{
	int	i;
	int err_check;

	i = 1;
	err_check = gettimeofday(&philo->time->now, NULL); // 현재 시간 받아오기
	if (err_check == -1)
		return (FAIL_GET_TIME);
	philo->time->now_in_ms = (philo->time->now.tv_sec * 1000) + (philo->time->now.tv_usec / 1000); // 현재 시간 체크
	philo->time->time_total = philo->time->now_in_ms - philo->time->start_in_ms; // 시간 차이 계산
	while (i < philo->time->philo_num + 1)
	{
		philo->time->check_total[i] = philo->time->now_in_ms - philo->time->check_in_ms[i];
		if (philo->time->check_total[i] >= philo->time->time_die)
		{
			print_status(philo, i, DIE);
			exit(EXIT_SUCCESS);
		}
		if (philo->time->exit_status == 1)
			exit(EXIT_SUCCESS);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philo		*philo;
	t_time		time;
	int 	i = -1;

	if (argc != 5 && argc != 6)
		return (put_error(FAIL_ARGC));
	if (parse_input(argc, argv, &time))
		return (put_error(FAIL_PARSE_INPUT));
	if (init_time(&time))
		return (put_error(FAIL_GET_TIME));
	if (malloc_time(&time) || malloc_thread(&philo, &time))
		return (put_error(FAIL_MALLOC));
	while (++i < philo->time->philo_num + 1)
		pthread_mutex_init(&philo->fork[i], NULL);
	i = -1;
	while (++i < philo->time->philo_num)
	{
		if (!(i % 2) && philo->is_even == ODD && i + 1== philo->time->philo_num)
			pthread_create(&(philo->thread[i]), NULL, (void *)thread_routine_last, (philo + i));
		else if (!(i % 2)) // if the number of philosophers is even number.
			pthread_create(&(philo->thread[i]), NULL, (void *)thread_routine_odd, (philo + i)); // index 0 is equivalent to the first philosopher.
		else if (i % 2)
			pthread_create(&(philo->thread[i]), NULL, (void *)thread_routine_even, (philo + i));
	}
	i = -1;
	while (check_time_die(philo) == 1)
		usleep(MILLISECOND / 10);
	while (++i < philo->time->philo_num)
		pthread_detach(philo->thread[i]);
	return (SUCCESS);
}