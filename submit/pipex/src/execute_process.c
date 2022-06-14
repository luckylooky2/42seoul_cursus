/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/14 17:36:20 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_parent_process(t_aux *aux, t_fd *fd)
{
	pid_t	pid;
	pid_t	comp_pid;
	int		i;

	i = 0;
	close_pipes(fd);
	pid = 0;
	while (i < aux->fork_num)
	{
		comp_pid = aux->pid[i];
		while (pid != comp_pid)
			pid = waitpid(comp_pid, &aux->status, WNOHANG);
		i++;
	}
	exit(WEXITSTATUS(aux->status));
}

void	execute_child_process(char *envp[], t_fd *fd, t_aux *aux)
{
	if (aux->pid[0] == 0)
		execute_first_child(envp, fd, aux);
	else if (aux->pid[aux->fork_num - 1] == 0)
		execute_last_child(envp, fd, aux);
	else
		execute_middle_child(envp, fd, aux);
}
