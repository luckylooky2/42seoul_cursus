/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:43:23 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/24 11:22:14 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

# define INT_MAX		2147483647
# define OVER_INT_MAX	2147483648LL

# define ODD	1
# define EVEN	2

typedef int	t_bool;
# define FALSE	0
# define TRUE	1

# define TIME_TOTAL		1
# define CHECK_TOTAL	2

# define MILLISECOND		1000

# define EXIT				1
# define SUCCESS			0
# define FAIL_ARGC			-1
# define FAIL_PARSE_INPUT	-2
# define FAIL_GET_TIME		-3
# define FAIL_MALLOC		-4
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
	struct timeval	start;
	struct timeval	now;
	struct timeval	check;
	size_t			start_in_ms;
	size_t			now_in_ms;
	size_t			*check_in_ms;
	size_t			*check_total;
	size_t			time_total;
	int				fail;
}	t_time;

typedef struct s_philo
{
	int				index;
	int				is_even;
	int				must_eat;
	t_time			*time;
	pthread_mutex_t	*fork;
	pthread_t		*thread;
	pthread_mutex_t	*print;
	int				*exit_status;
}	t_philo;

char		**ft_split(char const *s, char c);

int			init_time(t_time *time);
int			init_mutex(t_philo *philo);
void		init_check_time(t_philo *philo);

int			parse_input(char *argv[], t_time *time);
long long	ft_atoi(const char *nptr);
size_t		ft_strlen(const char *s);

int			malloc_time(t_time *time);
int			malloc_thread(t_philo **philo, t_time *time);
void		*ft_calloc(size_t nmemb, size_t size);

size_t		convert_to_millisecond(struct timeval time);
size_t		calculate_time(t_philo *philo, int index, int flag);
void		wait_time(t_philo *philo, unsigned int time_wait);

int			print_error(int err_code);
int			print_status(t_philo *philo, int philo_idx, int status);

int			create_thread(t_philo *philo);
int			detach_thread(t_philo *philo);
int			destroy_mutex(t_philo *philo);

void		thread_routine_odd(t_philo *philo);
void		thread_routine_even(t_philo *philo);
void		thread_routine_last(t_philo *philo);

int			monitor_time_die(t_philo *philo);

void		take_fork(t_philo *philo, int fork_index);
void		eat_dinner(t_philo *philo, int first, int second);
void		sleep_on_bed(t_philo *philo);
void		think_for_a_while(t_philo *philo);

#endif
