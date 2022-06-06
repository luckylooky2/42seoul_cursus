/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:34:12 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/07 00:13:55 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_aux
{
	pid_t	*pid;
	char	***exec_param;
	char	**path;
	int		argc;
	int		cmd_num;
	int		fork_num;
	int		here_doc;
	char	*limiter;
	int		status;
}	t_aux;

typedef struct s_fd
{
	int	**pipe;
	int	infile;
	int	outfile;
	int argc;
	int	pipe_num;
}	t_fd;

#endif