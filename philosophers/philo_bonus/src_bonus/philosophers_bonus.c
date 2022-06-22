/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:33:53 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/22 19:52:23 by chanhyle         ###   ########.fr       */
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
	sem_unlink("/fork");
	sem = sem_open("/fork", O_CREAT, 0644, 1);
	if (sem  == SEM_FAILED)
		printf("1111\n");
	// sem_getvalue(sem, &sval);
	// printf("sval : %d\n", sval); 
	pid = fork();
	if (pid == 0)
	{
		printf("111\n");
		printf("222\n");
		// res = sem_wait(sem);
		printf("4\n");
		res = sem_wait(sem);
		printf("5\n");
		res = sem_wait(sem);
		printf("6\n");
		res = sem_wait(sem);
		printf("333\n");
		printf("child : %p\n", sem);
	}
	else
	{
		printf("parent : %p\n", sem);
		printf("1\n");
		sem_post(sem);
		printf("2\n");
		sem_post(sem);
		printf("3\n");
		wait(&sval);
	}
	return (SUCCESS);
}
