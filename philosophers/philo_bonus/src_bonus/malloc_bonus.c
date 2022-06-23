/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:55:03 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 14:49:17 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	malloc_thread(t_philo *philo, t_time *time)
{
	pid_t	*pid;
	sem_t	*fork;
	sem_t	*print;

	pid = (pid_t *)ft_calloc(sizeof(pid_t), time->philo_num + 1);
	if (!pid)
		exit(print_error(FAIL_MALLOC));
	sem_unlink("fork");
	sem_unlink("print"); 
	fork = sem_open("fork", O_CREAT, 0600, ft_atoi(time->philo_num));
	print = sem_open("print", O_CREAT, 0600, 1);
	if (fork == SEM_FAILED || print == SEM_FAILED)
		exit(print_error(FAIL_MALLOC));
	if (time->philo_num % 2)
		philo->is_even = ODD;
	else
		philo->is_even = EVEN;
	philo->must_eat = time->must_eat;
	philo->time = time;
	philo->pid = pid;
	philo->fork = fork;
	philo->print = print;
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
