/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:51:11 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/27 01:29:54 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	get_time(t_time *time, int flag)
{
	struct timeval	second;
	int				err_check;

	err_check = gettimeofday(&second, NULL);
	if (err_check == -1)
		exit(print_error(FAIL_GET_TIME));
	if (flag == START)
		time->start_in_ms = convert_to_millisecond(second);
	else if (flag == NOW)
		time->now_in_ms = convert_to_millisecond(second);
	else if (flag == CHECK)
		time->check_in_ms = convert_to_millisecond(second);
}

void	init_time(t_time *time)
{
	get_time(time, START);
	get_time(time, CHECK);
	time->now_in_ms = 0;
	time->check_total = 0;
	time->time_total = 0;
}

void	init_check_time(t_philo *philo)
{
	int				err_check;
	struct timeval	check;

	err_check = gettimeofday(&check, NULL);
	if (err_check == -1)
		exit(print_error(FAIL_GET_TIME));
	philo->time->check_total = 0;
	philo->time->check_in_ms = convert_to_millisecond(check);
}
