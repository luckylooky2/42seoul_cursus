/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_proc_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:43:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 16:55:26 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	make_pipe(t_state *s)
{
	int	i;

	i = -1;
	while (s->pipe_cnt > ++i)
	{
		s->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (s->pipes[i] == NULL)
			panic_memory();
		if (pipe(s->pipes[i]) == -1)
			panic("Failed to create pipe.");
	}
}

static void	close_unused_pipe(t_state *s)
{
	int	i;

	i = 0;
	while (i < s->pipe_cnt)
	{
		// 이전 프로세스로부터 읽을 pipe는 닫지 않음
		if (s->pid[i + 1] != 0)
			close(s->pipes[i][READ]);
		// 현재 프로세스에서 write할 pipe는 닫지 않음
		if (s->pid[i] != 0)
			close(s->pipes[i][WRITE]);
		i++; 
	}
}

void	make_proc_pipe(t_state *s)
{
	int	i;

	s->pipes-> NULL;
	s->pid = NULL;
	if (s->pipe_cnt != 0)
	{
		s->pipes = (int **)malloc(sizeof(int *) * s->pipe_cnt);
		if (s->pipes == NULL)
			panic_memory();
	}
	s->pid = (pid_t *)malloc(sizeof(pid_t) * s->pid_cnt);
	if (s->pid == NULL)
		panic_memory();
	i = -1;
	while (++i < s->pid_cnt)
		s->pid[i] = 1;
	make_pipe(s);
	make_proc(s);
	close_unused_pipe(s);
}