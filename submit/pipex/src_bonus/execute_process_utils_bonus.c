/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:37:19 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/14 10:35:07 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	close_pipes(t_fd *fd)
{
	int	i;

	i = 0;
	while (i < fd->pipe_num)
	{
		close(fd->pipe[i][0]);
		close(fd->pipe[i][1]);
		i++;
	}
}

int	check_nth_child_process(t_aux *aux)
{
	int	nth;

	nth = 0;
	while (nth < aux->fork_num)
	{
		if (aux->pid[nth] == 0)
			return (nth);
		nth++;
	}
	return (0);
}

int	check_limiter(t_aux *aux, char *line)
{
	int		i;
	int		cnt;
	int		limiter_num;
	int		line_num;
	char	*new_limiter;

	i = 0;
	cnt = 0;
	new_limiter = ft_strjoin(aux->limiter, "\n");
	if (new_limiter == NULL)
		exit(EXIT_FAILURE);
	limiter_num = ft_strlen(new_limiter);
	line_num = ft_strlen(line);
	if (limiter_num != line_num)
		return (0);
	if (ft_strncmp(new_limiter, line, limiter_num) == 0)
	{
		free(new_limiter);
		return (1);
	}
	free(new_limiter);
	return (0);
}

char	*get_next_line_with_limiter(t_aux *aux)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	while (1)
	{
		tmp = get_next_line(STDIN_FILENO);
		if (tmp == NULL)
			exit(EXIT_FAILURE);
		if (check_limiter(aux, tmp) == 1)
		{
			free(tmp);
			break ;
		}
		line = ft_strjoin_free(&line, tmp, 0);
		free(tmp);
	}
	return (line);
}
