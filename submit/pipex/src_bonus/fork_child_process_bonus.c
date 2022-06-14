/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_child_process_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:00:47 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/14 18:50:00 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	fork_child_process(t_aux *aux)
{
	int	i;

	i = 1;
	aux->pid[0] = fork();
	if (aux->pid[0] == -1)
		exit(EXIT_FAILURE);
	while (i < aux->fork_num)
	{
		if (check_child_process(aux) == 0)
			aux->pid[i] = fork();
		if (aux->pid[i] == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}
