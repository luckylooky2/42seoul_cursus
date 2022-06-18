/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:43:23 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/18 10:20:24 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h> //Compile and link with -pthread
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

# define INT_MAX		2147483647
# define OVER_INT_MAX	2147483648LL

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
	size_t			start_in_ms;
	size_t			time_total;
}	t_time;

typedef struct	s_philo
{
	int				index;
	struct timeval	check;
	struct timeval	now;
	size_t			check_in_ms;
	size_t			now_in_ms;
	size_t			check_total;
	int				must_eat;
	t_time			*time; // 공유 자원
	pthread_mutex_t	*fork; // 공유 자원
	pthread_t		*thread; // 공유 자원
}	t_philo;

char		**ft_split(char const *s, char c);
long long	ft_atoll(const char *nptr);
long long	ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(const char *s);

#endif