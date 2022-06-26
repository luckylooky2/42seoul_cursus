/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 01:23:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/27 01:25:03 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"


void	fork_child_process(t_philo *philo)
{
	int	i;

	i = 1;
	philo->pid[0] = fork();
	if (philo->pid[0] == -1)
		exit(FAIL_FORK);
	while (i < philo->time->philo_num)
	{
		if (check_child_process(philo) == FALSE)
			philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			exit(FAIL_FORK);
		i++;
	}
}
