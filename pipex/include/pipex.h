/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:34:12 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/05 16:50:35 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "get_next_line.h"

typedef struct s_aux
{
	pid_t	*pid;
	char	***exec_param;
	char	**path;
	char 	*str_infile;
	int		argc;
	int		cmd_num;
	int		fork_num;
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

char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_free(char **s1, char *s2, int flag);
char	*ft_strjoin(char const *s1, char const *s2);

#endif