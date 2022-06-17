/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:42:59 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/17 19:32:01 by chanhyle         ###   ########.fr       */
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
	int	diff;
	int diff_eat_sleep;
	
	err_check = gettimeofday(&philo->time->now, NULL);
	if (err_check == -1)
		return (FAIL_GET_TIME);
	if (status == EAT)
	{
		err_check = gettimeofday(&philo->check, NULL);
		if (err_check == -1)
			return (FAIL_GET_TIME);
		philo->check_total = 0;
	}
	philo->time->now_in_ms = (philo->time->now.tv_sec * 1000) + (philo->time->now.tv_usec / 1000); // 현재 시간 체크
	philo->check_in_ms = (philo->check.tv_sec * 1000) + (philo->check.tv_usec / 1000); // 기준 시간 체크
	philo->time->time_total = philo->time->now_in_ms - philo->time->start_in_ms;
	philo->check_total = philo->time->now_in_ms - philo->check_in_ms;
	if (philo->time->time_eat >= philo->time->time_sleep)
		diff_eat_sleep = philo->time->time_eat - philo->time->time_sleep;
	else
		diff_eat_sleep = philo->time->time_sleep - philo->time->time_eat;
	if (status == EAT && philo->check_total + philo->time->time_eat > philo->time->time_die && philo->check_in_ms != 0)
	{
		print_status(philo, philo_idx, status); // eat
		diff = philo->time->time_die - philo->check_total;
		usleep(diff * MILLISECOND);
		philo->time->time_total += diff;
		print_status(philo, philo_idx, DIE);
	}
	if (status == SLEEP && philo->check_total + philo->time->time_sleep > philo->time->time_die && philo->check_in_ms != 0)
	{
		print_status(philo, philo_idx, status); // sleep
		diff = philo->time->time_die - philo->check_total;
		usleep(diff * MILLISECOND);
		philo->time->time_total += diff;
		print_status(philo, philo_idx, DIE);
	}
	if (status == THINK && philo->check_total + diff_eat_sleep > philo->time->time_die && philo->check_in_ms != 0)
	{
		print_status(philo, philo_idx, status); // sleep
		diff = philo->time->time_die - philo->check_total;
		if (diff < 0)
			diff = 0;
		usleep(diff * MILLISECOND);
		philo->time->time_total += diff;
		print_status(philo, philo_idx, DIE);
	}
	print_status(philo, philo_idx, status);
	return (1);
}

size_t get_now(void)
{
	struct	timeval now;
	int		err_check;

	err_check = gettimeofday(&now, NULL);
	if (err_check == -1)
		return (0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	wait_time(unsigned int wait)
{
	size_t	target;
	
	target = wait + get_now();
	while (target > get_now())
		usleep(200);
}

int	thread_routine_odd(void *arg)
{
	t_philo *philo;
	int		philo_idx;
	int		eat;
	int		i;

	i = -1;	
	philo = (t_philo *)arg;
	philo_idx = philo->index;
	if (philo->time->must_eat == 0)
		eat = -1;
	else
		eat = philo->time->must_eat;
	usleep(50 * (philo->time->philo_num / 4 + 1));
	while (eat)
	{
		pthread_mutex_lock(&philo->fork[philo_idx]);
		print_time(philo, philo_idx, FORK);
		pthread_mutex_lock(&philo->fork[philo_idx + 1]);
		print_time(philo, philo_idx + 1, FORK);
		print_time(philo, philo_idx, EAT);
		wait_time(philo->time->time_eat);
		pthread_mutex_unlock(&philo->fork[philo_idx + 1]);
		pthread_mutex_unlock(&philo->fork[philo_idx]);
		print_time(philo, philo_idx, SLEEP);
		wait_time(philo->time->time_sleep);
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
	int		i;
	
	i = -1;
	philo = (t_philo *)arg;
	philo_idx = philo->index;
	if (philo->time->must_eat == 0)
		eat = -1;
	else
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
		wait_time(philo->time->time_eat);
		pthread_mutex_unlock(&philo->fork[philo_idx]);
		if (philo_idx != philo->time->philo_num)
			pthread_mutex_unlock(&philo->fork[philo_idx + 1]);
		else
			pthread_mutex_unlock(&philo->fork[1]);
		print_time(philo, philo_idx, SLEEP);
		wait_time(philo->time->time_sleep);
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
	time->now_in_ms = 0;
	time->time_total = 0;
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
		check_size_t = ft_atoui(argv[i]);
		if (check_size_t > 4294967295LL)
			return (0);
		i++;
	}
	return (1);
}

int	parse_input(int argc, char *argv[], t_time *time)
{
	if (check_number(argv) == 0)
		return (FAIL_PARSE_INPUT);
	time->philo_num = ft_atoui(argv[1]);
	time->time_die = ft_atoui(argv[2]);
	time->time_eat = ft_atoui(argv[3]);
	time->time_sleep = ft_atoui(argv[4]);
	time->must_eat = ft_atoui(argv[5]);
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
		else if (i % 2 == 1)
			pthread_create(&(philo->thread[i]), NULL, (void *)thread_routine_even, (void *)(philo + i));
	}
	i = -1;
	// while (1)
	// {
	// 	// 스레드가 죽으면 break;
	// }
	// while (++i < philo->time->philo_num)
	// 	pthread_detach(philo->thread[i]);
	while (++i < philo->time->philo_num)
		pthread_join(philo->thread[i], NULL);
	return (SUCCESS);
}