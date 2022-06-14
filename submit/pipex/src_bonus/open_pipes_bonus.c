/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:00:11 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/14 10:35:47 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	open_pipes(t_fd *fd)
{
	int	i;

	i = 0;
	fd->pipe = (pid_t **)ft_calloc(sizeof(pid_t *), fd->pipe_num);
	if (fd->pipe == NULL)
		exit(EXIT_FAILURE);
	while (i < fd->pipe_num)
	{
		fd->pipe[i] = (pid_t *)ft_calloc(sizeof(pid_t), 2);
		if (fd->pipe[i] == NULL)
			exit(EXIT_FAILURE);
		if (pipe(fd->pipe[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}
