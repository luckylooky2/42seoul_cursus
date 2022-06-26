/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:33:53 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/27 02:17:47 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	main(int argc, char *argv[])
{
	t_time	time;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		exit(print_error(FAIL_ARGC));
	parse_input(argv, &time);
	init_time(&time);
	malloc_philo(&philo, &time);
	fork_child_process(philo);
	if (check_child_process(philo) == TRUE)
		execute_child_process(philo);
	else
		execute_parent_process(philo);
	return (SUCCESS);
}
