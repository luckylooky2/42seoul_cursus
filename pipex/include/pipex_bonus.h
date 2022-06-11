/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:34:12 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 19:14:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define EXIT_NO_FILE		1
# define EXIT_NO_COMMAND	127

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
	int	argc;
	int	pipe_num;
}	t_fd;

void	init_struct(int argc, t_fd *fd, t_aux *aux);
void	init_struct_here_doc(int argc, char *argv[], t_fd *fd, t_aux *aux);
int		check_child_process(t_aux *aux);
void	check_here_doc(char *argv[], t_aux *aux);

void	execute_parent_process(t_aux *aux, t_fd *fd);
void	execute_child_process(char *envp[], t_fd *fd, t_aux *aux);

void	execute_first_child(char *envp[], t_fd *fd, t_aux *aux);
void	execute_last_child(char *envp[], t_fd *fd, t_aux *aux);
void	execute_middle_child(char *envp[], t_fd *fd, t_aux *aux);

void	close_pipes(t_fd *fd);
int		check_nth_child_process(t_aux *aux);
int		check_limiter(t_aux *aux, char *line);
char	*get_next_line_with_limiter(t_aux *aux);

void	parse_input(char *argv[], char *envp[], t_aux *aux);

int		find_path(char *envp[]);
void	free_path(char ***path_ary);

void	open_files(char *argv[], t_aux *aux, t_fd *fd);
void	open_pipes(t_fd *fd);
void	fork_child_process(t_aux *aux);

#endif