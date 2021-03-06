/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:59:29 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 18:59:43 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files(char *argv[], t_aux *aux, t_fd *fd)
{
	if (aux->here_doc == 0)
	{
		fd->infile = open(argv[1], O_RDONLY);
		if (fd->infile < 0)
		{
			write(2, "no such file or directory: ", 28);
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, "\n", 1);
		}
	}
	if (aux->here_doc == 0)
		fd->outfile = open(argv[fd->argc - 1],
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (aux->here_doc == 1)
		fd->outfile = open(argv[fd->argc - 1],
				O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd->outfile < 0)
		exit(EXIT_FAILURE);
}
