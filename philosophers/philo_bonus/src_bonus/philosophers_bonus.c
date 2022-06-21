/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:33:53 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/21 22:13:53 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	main(int argc, char *argv[])
{
	t_time	time;
	pid_t	pid;
	sem_t	*sem;
	int		res;
	int		sval;

	res = 0;
	// if (argc != 5 && argc != 6)
	// 	exit(print_error(FAIL_ARGC));
	// parse_input(argv, &time);
	// init_time(&time);
	// sem = (sem_t *)malloc(sizeof(sem_t) * 1);
	// sem_unlink("fork");
	if (sem_open("fork", O_CREAT , 0644, 1) == SEM_FAILED)
		printf("1111\n");
	// sem_getvalue(sem, &sval);
	// printf("sval : %d\n", sval); 
	pid = fork();
	if (pid == 0)
	{
		res = sem_wait(sem);
		res = sem_wait(sem);
		// sem_post(sem);
		printf("res : %d\n", res);
		printf("child : %d\n", *sem);
	}
	else
	{
		printf("parent : %d\n", *sem);
	}
	return (SUCCESS);
}
