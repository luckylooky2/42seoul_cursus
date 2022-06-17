/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:43:23 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/17 21:17:06 by chanhyle         ###   ########.fr       */
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
# include <limits.h>

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
	unsigned int	philo_num;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	must_eat;
	struct timeval	start;
	struct timeval	now;
	size_t			start_in_ms;
	size_t			now_in_ms;
	size_t			time_total;
}	t_time;

typedef struct	s_philo
{
	int				index;
	struct timeval	check;
	size_t			check_in_ms;
	size_t			check_total;
	t_time			*time; // 공유 자원
	pthread_mutex_t	*fork; // 공유 자원
	pthread_t		*thread; // 공유 자원
}	t_philo;

char		**ft_split(char const *s, char c);
long long	ft_atoll(const char *nptr);
size_t		ft_atoui(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(const char *s);

#endif