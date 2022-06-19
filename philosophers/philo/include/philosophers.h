/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:43:23 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/19 22:23:04 by chanhyle         ###   ########.fr       */
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

# define MILLISECOND		1000

# define SUCCESS			0
# define FAIL_ARGC			-1
# define FAIL_PARSE_INPUT	-2
# define FAIL_GET_TIME		-3
# define FAIL_MALLOC		-4

# define FORK	1
# define EAT	2
# define SLEEP	3
# define THINK	4
# define DIE	5

typedef struct	s_time
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
	int				exit_status;
}	t_time;

typedef struct	s_philo
{
	int				index;
	int				is_even;
	int				flag;
	int				must_eat;
	t_time			*time; // 공유 자원
	pthread_mutex_t	*fork; // 공유 자원
	pthread_t		*thread; // 공유 자원
}	t_philo;

char		**ft_split(char const *s, char c);
long long	ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(const char *s);

#endif