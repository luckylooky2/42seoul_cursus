/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 01:35:22 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/27 01:58:11 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	monitor_time_die(t_philo *philo)
{
	int	index;

	index = check_nth_child_process(philo) + 1;
	get_time(philo->time, NOW);
	philo->time->check_total = calculate_time(philo, CHECK_TOTAL);
	if (philo->time->check_total >= (size_t)philo->time->time_die)
		print_status(philo, index, DIE);
	return (SUCCESS);
}
