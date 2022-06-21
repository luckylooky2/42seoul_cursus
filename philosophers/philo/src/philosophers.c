/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:42:59 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/21 19:20:25 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_time	time;

	if (argc != 5 && argc != 6)
		return (print_error(FAIL_ARGC));
	if (parse_input(argv, &time))
		return (print_error(FAIL_PARSE_INPUT));
	if (init_time(&time))
		return (print_error(FAIL_GET_TIME));
	if (malloc_time(&time) || malloc_thread(&philo, &time))
		return (print_error(FAIL_MALLOC));
	if (init_mutex(philo))
		return (print_error(FAIL_INIT_MUTEX));
	if (create_thread(philo))
		return (print_error(FAIL_CREATE_THREAD));
	while (monitor_time_die(philo) == SUCCESS)
		usleep(MILLISECOND / 10);
	if (detach_thread(philo))
		return (print_error(FAIL_DETACH_THREAD));
	if (destroy_mutex(philo))
		return (print_error(FAIL_DESTROY_MUTEX));
	return (SUCCESS);
}
