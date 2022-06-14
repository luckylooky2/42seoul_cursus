/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:03:07 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/14 10:36:06 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	init_struct(int argc, t_fd *fd, t_aux *aux)
{
	int	i;

	i = 0;
	fd->pipe = NULL;
	fd->infile = 0;
	fd->outfile = 0;
	fd->argc = argc;
	fd->pipe_num = argc - 4;
	aux->exec_param = NULL;
	aux->path = NULL;
	aux->argc = argc;
	aux->cmd_num = argc - 3;
	aux->fork_num = argc - 3;
	aux->limiter = NULL;
	aux->status = 0;
	aux->pid = (pid_t *)ft_calloc(sizeof(pid_t), aux->fork_num);
	if (aux->pid == NULL)
		exit(EXIT_FAILURE);
	while (i < argc - 2)
		aux->pid[i++] = 1;
}

void	init_struct_here_doc(int argc, char *argv[], t_fd *fd, t_aux *aux)
{
	int	i;

	i = 0;
	fd->pipe = NULL;
	fd->infile = 0;
	fd->outfile = 0;
	fd->argc = argc;
	fd->pipe_num = argc - 4;
	aux->exec_param = NULL;
	aux->path = NULL;
	aux->argc = argc;
	aux->cmd_num = argc - 4;
	aux->fork_num = argc - 3;
	aux->limiter = argv[2];
	aux->status = 0;
	aux->pid = (pid_t *)ft_calloc(sizeof(pid_t), aux->fork_num);
	if (aux->pid == NULL)
		exit(EXIT_FAILURE);
	while (i < argc - 3)
		aux->pid[i++] = 1;
}

int	check_child_process(t_aux *aux)
{
	int	i;

	i = 0;
	while (i < aux->fork_num)
	{
		if (aux->pid[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

void	check_here_doc(char *argv[], t_aux *aux)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (ft_strlen(argv[1]) != 8)
	{
		aux->here_doc = 0;
		return ;
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		aux->here_doc = 1;
		return ;
	}
	aux->here_doc = 0;
	return ;
}
