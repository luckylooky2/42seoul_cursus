/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:09:58 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/21 19:22:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_exit_status(t_philo *philo)
{
	int	i;

	i = 1;
	while (i < philo->time->philo_num + 1)
	{
		if (philo->exit_status[i] == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	monitor_time_die(t_philo *philo)
{
	int	i;
	int	err_check;

	i = 1;
	err_check = gettimeofday(&philo->time->now, NULL);
	if (err_check == -1)
	{
		print_error(FAIL_GET_TIME);
		return (EXIT);
	}
	philo->time->now_in_ms = convert_to_millisecond(philo->time->now);
	philo->time->time_total = calculate_time(philo, 0, TIME_TOTAL);
	while (i < philo->time->philo_num + 1)
	{
		philo->time->check_total[i] = calculate_time(philo, i, CHECK_TOTAL);
		if (philo->time->check_total[i] >= (size_t)philo->time->time_die)
			return (print_status(philo, i, DIE));
		if (check_exit_status(philo) == TRUE || philo->time->fail == TRUE)
			return (EXIT);
		i++;
	}
	return (SUCCESS);
}
