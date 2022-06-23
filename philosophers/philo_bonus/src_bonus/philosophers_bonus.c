/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:33:53 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/23 21:17:05 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

t_bool	check_child_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->time->philo_num)
	{
		if (philo->pid[i] == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	fork_child_process(t_philo *philo)
{
	int	i;

	i = 1;
	philo->pid[0] = fork();
	if (philo->pid[0] == -1)
		exit(EXIT_FAILURE);
	while (i < philo->time->philo_num)
	{
		if (check_child_process(philo) == FALSE)
			philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_time	time;
	t_philo	*philo;
	int		res = 0;
	int		sval = 0;

	res = 0;
	if (argc != 5 && argc != 6)
		exit(print_error(FAIL_ARGC));
	parse_input(argv, &time);
	init_time(&time);
	malloc_thread(&philo, &time);
	fork_child_process(philo);
	if (check_child_process(philo) == TRUE)
		execute_child_process(philo);
	else
		execute_parent_process(philo);
	return (SUCCESS);
}

 // semaphore는 mutex처럼 기다리는 것이 아니라, 값으로 판단하는 듯?
 // wait와 post가 동일한 개수로 짝을 이루면, 순서에 상관없이(post를 먼저하고 wait을 그 다음에 해도 동작함) 동작함
 // wait가 post보다 한 개 더 많다면, post를 기다림

 // hseong님 wait()
 // 자식 프로세스는 종료될 때, pid를 반환하는데 이 pid를 받아줄 wait 함수가 존재하지 않는다면 제대로 종료되지 않음 => 좀비 프로세스가 되는 이유