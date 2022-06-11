/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 19:06:38 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	execute_parent_process(t_aux *aux, t_fd *fd)
{
	pid_t	pid;
	pid_t	last_pid;

	pid = 0;
	last_pid = aux->pid[aux->fork_num - 1];
	close_pipes(fd);
	while (pid != last_pid)
		pid = waitpid(last_pid, &aux->status, WNOHANG);
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
