/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:12 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 19:14:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	execve_command(char *envp[], t_aux *aux, int num)
{
	int	path_len;

	path_len = ft_strlen(aux->path[num]);
	if (execve(aux->path[num], aux->exec_param[num], envp) == -1)
	{
		if (aux->path[num][0] == '/')
		{
			perror(aux->path[num]);
			exit(EXIT_NO_FILE);
		}
		else
		{
			write(STDERR_FILENO, aux->path[num], path_len);
			write(STDERR_FILENO, " : command not found\n", 22);
			exit(EXIT_NO_COMMAND);
		}
	}
}

void	execute_first_child(char *envp[], t_fd *fd, t_aux *aux)
{
	char	*line;

	line = NULL;
	if (aux->here_doc == 0)
	{
		dup2(fd->infile, STDIN_FILENO);
		dup2(fd->pipe[0][1], STDOUT_FILENO);
		close_pipes(fd);
		execve_command(envp, aux, 0);
	}
	else if (aux->here_doc == 1)
	{
		line = get_next_line_with_limiter(aux);
		dup2(fd->pipe[0][1], STDOUT_FILENO);
		close_pipes(fd);
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
		exit(EXIT_SUCCESS);
	}
}

void	execute_last_child(char *envp[], t_fd *fd, t_aux *aux)
{
	int	last;

	last = aux->cmd_num - 1;
	dup2(fd->pipe[fd->pipe_num - 1][0], STDIN_FILENO);
	dup2(fd->outfile, STDOUT_FILENO);
	close_pipes(fd);
	execve_command(envp, aux, last);
}

void	execute_middle_child(char *envp[], t_fd *fd, t_aux *aux)
{
	int	nth;
	int	path_len;

	nth = check_nth_child_process(aux);
	path_len = ft_strlen(aux->path[nth - 1]);
	dup2(fd->pipe[nth - 1][0], STDIN_FILENO);
	dup2(fd->pipe[nth][1], STDOUT_FILENO);
	close_pipes(fd);
	execve_command(envp, aux, nth - 1);
}
