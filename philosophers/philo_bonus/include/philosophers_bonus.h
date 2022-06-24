/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:34:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/24 11:27:35 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILOSOPHERS_BONUS_H
#define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>

# define INT_MAX		2147483647
# define OVER_INT_MAX	2147483648LL

# define ODD	1
# define EVEN	2

typedef int		t_bool;
# define FALSE	0
# define TRUE	1

# define START	1
# define NOW	2
# define CHECK	3

# define TIME_TOTAL		1
# define CHECK_TOTAL	2

# define MILLISECOND		1000
	
# define EXIT_TIME_DIE		100
# define EXIT_MUST_EAT		101

# define EXIT				1
# define SUCCESS			0
# define FAIL_ARGC			-1
# define FAIL_PARSE_INPUT	-2
# define FAIL_GET_TIME		-3
# define FAIL_MALLOC		-4
# define FAIL_SEMAPHORE		-10
# define FAIL_INIT_MUTEX	-5
# define FAIL_CREATE_THREAD	-6
# define FAIL_DETACH_THREAD	-7
# define FAIL_DESTROY_MUTEX	-8

# define FORK	1
# define EAT	2
# define SLEEP	3
# define THINK	4
# define DIE	5

typedef struct s_time
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	size_t			start_in_ms;
	size_t			now_in_ms;
	size_t			check_in_ms;
	size_t			check_total;
	size_t			time_total;
	int				fail;
}	t_time;

typedef struct s_philo
{
	int				is_even;
	int				must_eat;
	pid_t			*pid;
	t_time			*time;
	sem_t			*fork;
	pthread_t		*thread;
	sem_t			*print;
	sem_t			*exit_status;
	int				status;
}	t_philo;

void	parse_input(char *argv[], t_time *time);
long long	ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
void	malloc_thread(t_philo **philo, t_time *time);

void	init_time(t_time *time);
void	init_check_time(t_philo *philo);
int	print_error(int err_code);
void	print_status(t_philo *philo, int philo_idx, int status);

void	parse_input(char *argv[], t_time *time);
size_t	convert_to_millisecond(struct timeval time);
size_t	calculate_time(t_philo *philo, int flag);
void	wait_time(t_philo *philo, unsigned int time_wait);

void	*ft_calloc(size_t nmemb, size_t size);

int	check_nth_child_process(t_philo *philo);
void	execute_parent_process(t_philo *philo);
void	execute_child_process(t_philo *philo);

void	execute_odd_child(t_philo *philo);
void	execute_even_child(t_philo *philo);
void	execute_last_child(t_philo *philo);

void	take_fork(t_philo *philo, int index);
void	eat_dinner(t_philo *philo, int index);
void	sleep_on_bed(t_philo *philo, int index);
void	think_for_a_while(t_philo *philo, int index);

#endif