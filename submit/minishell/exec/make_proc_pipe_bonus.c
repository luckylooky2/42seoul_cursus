/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_proc_pipe_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:27:29 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/28 15:57:12 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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

static void	make_proc(t_state *s)
{
	int	i;
	int	j;
	int	is_child;

	i = -1;
	while (s->pid_cnt > ++i)
	{
		is_child = 0;
		j = -1;
		while (s->pid_cnt > ++j)
		{
			if (s->pid[j] == 0)
				is_child = 1;
		}
		if (!is_child)
		{
			s->pid[i] = fork();
			if (s->pid[i] == -1)
				panic("Failed to create process.");
		}
	}
}

static void	close_unused_pipe(t_state *s)
{
	int	i;

	i = 0;
	while (i < s->pipe_cnt)
	{
		if (s->pid[i + 1] != 0)
			close(s->pipes[i][READ]);
		if (s->pid[i] != 0)
			close(s->pipes[i][WRITE]);
		i++;
	}
}

void	make_proc_pipe(t_state *s)
{
	int	i;

	s->pipes = NULL;
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
