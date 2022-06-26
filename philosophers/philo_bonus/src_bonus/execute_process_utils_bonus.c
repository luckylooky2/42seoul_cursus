/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 01:37:01 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/27 01:37:16 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	check_nth_child_process(t_philo *philo)
{
	int	nth;

	nth = 0;
	while (nth < philo->time->philo_num)
	{
		if (philo->pid[nth] == 0)
			return (nth);
		nth++;
	}
	return (0);
}
