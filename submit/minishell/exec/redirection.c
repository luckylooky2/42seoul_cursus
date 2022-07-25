/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 00:45:34 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 21:59:12 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	input_redirection_helper(char *str)
{
	if (str[0] != '<')
		return (ft_atoi(str));
	else
		return (open(str + 2, O_RDONLY));
}

int	input_redirection(t_state *s, t_deq *input_files, int n)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = -1;
	if (0 < n)
		fd = s->pipes[n - 1][READ];
	while (i < input_files->size)
	{
		close(fd);
		fd = input_redirection_helper(ft_deq_get(input_files, i)->data);
		if (fd == -1)
		{
			error_errno(ft_deq_get(input_files, i)->data);
			return (-1);
		}
		i++;
	}
	if (fd != -1 && dup2(fd, STDIN_FILENO) == -1 && close(fd) == -1)
	{
		error_errno("dup2");
		return (-1);
	}
	return (0);
}

static int	output_redirection_helper(char *str)
{
	if (str[1] == '>')
		return (open(str + 3, O_WRONLY | O_CREAT | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	else
		return (open(str + 2, O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
}

int	output_redirection(t_state *s, t_deq *output_files, int n)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = -1;
	if (n < s->pipe_cnt)
		fd = s->pipes[n][WRITE];
	while (i < output_files->size)
	{
		close(fd);
		fd = output_redirection_helper(ft_deq_get(output_files, i)->data);
		if (fd == -1)
		{
			error_errno(ft_deq_get(output_files, i)->data);
			return (-1);
		}
		i++;
	}
	if (fd != -1 && dup2(fd, STDOUT_FILENO) == -1 && close(fd) == -1)
	{
		error_errno("dup2");
		return (-1);
	}
	return (0);
}
