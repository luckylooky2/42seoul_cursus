/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:35:15 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/14 16:11:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_fd	fd;
	t_aux	aux;

	check_here_doc(argv, &aux);
	if (aux.here_doc == 0)
		init_struct(argc, &fd, &aux);
	else if (aux.here_doc == 1)
		init_struct_here_doc(argc, argv, &fd, &aux);
	if ((aux.here_doc == 0 && argc < 5) || (aux.here_doc == 1 && argc < 6))
		exit(EXIT_FAILURE);
	parse_input(argv, envp, &aux);
	open_files(argv, &aux, &fd);
	open_pipes(&fd);
	fork_child_process(&aux);
	if (check_child_process(&aux) == 1)
		execute_child_process(envp, &fd, &aux);
	else
		execute_parent_process(&aux, &fd);
	exit(aux.status);
}
