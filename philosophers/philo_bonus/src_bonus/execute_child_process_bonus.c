/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:12 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/24 18:49:44 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	execute_odd_child(t_philo *philo)
{	
	int	index;

	index = check_nth_child_process(philo) + 1;
	while (philo->must_eat)
	{
		take_fork(philo, index);
		eat_dinner(philo, index);
		sleep_on_bed(philo, index);
		think_for_a_while(philo, index);
	}
}
