/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:35:15 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/04 17:32:25 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// void	free_c_params(t_param **param)
// {
// 	int	i;

// 	i = 0;
// 	if ((*param)->cmd1 != NULL)
// 	{
// 		while ((*param)->cmd1[i])
// 		{
// 			free((*param)->cmd1[i]);
// 			i++;
// 		}
// 		free((*param)->cmd1);
// 	}
// 	i = 0;
// 	if ((*param)->cmd2 != NULL)
// 	{
// 		while ((*param)->cmd2[i])
// 		{
// 			free((*param)->cmd2[i]);
// 			i++;
// 		}
// 		free((*param)->cmd2);
// 	}
// }

void	parse_input(char *argv[], t_aux *aux)
{
	int	i;

	i = 0;
	aux->exec_param = (char ***)ft_calloc(sizeof(char **), aux->cmd_num + 1);
	if (aux->exec_param == NULL)
		exit(EXIT_FAILURE);
	while (i < aux->cmd_num)
	{
		aux->exec_param[i] = ft_split(argv[i + 2], ' ');
		if (aux->exec_param[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	open_files(char *argv[], t_fd *fd)
{
	fd->infile = open(argv[1], O_RDONLY);
	fd->outfile = open(argv[fd->argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd->infile < 0 || fd->outfile < 0)
		exit(EXIT_FAILURE);
}

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

int	check_child_process(t_aux *aux)
{
	int	i;

	i = 0;
	while (i < aux->fork_num)
	{
		if (aux->pid[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

void	fork_child_process(t_aux *aux)
{
	int	i;

	i = 1;
	aux->pid[0] = fork();
	while (i < aux->fork_num)
	{
		if (check_child_process(aux) == 0)
			aux->pid[i] = fork();
		i++;
	}
}

char	*read_infile(t_fd *fd, t_aux *aux)
{
	char	*line;
	char	*ret;
	
	ret = NULL;
	while (1)
	{
		line = get_next_line(fd->infile);
		if (line == NULL)
			break ;
		ret = ft_strjoin(&ret, line);
		if (ret == NULL)
			exit(EXIT_FAILURE);
		free(line);
	}
	// system("leaks pipex");
	return (ret);
}

void	execute_child_process(t_fd *fd, t_aux *aux)
{
	if (aux->pid[0] == 0) // 첫 번째 자식
	{
		aux->str_infile = read_infile(fd, aux);
		dup2(fd->pipe[0][1], STDOUT_FILENO);
		close(fd->pipe[0][0]);
		close(fd->pipe[1][0]);
		close(fd->pipe[1][1]);
		write(1, aux->str_infile, ft_strlen(aux->str_infile));
	}
	else if (aux->pid[aux->fork_num - 1] == 0)// 마지막 자식
	{
		dup2(fd->pipe[1][0], 0);
        dup2(fd->outfile, 1);
        close(fd->pipe[1][1]);
        close(fd->pipe[0][0]);
        close(fd->pipe[0][1]);
        if (execve("/usr/bin/wc", aux->exec_param[1], NULL) == -1)
            printf("failed c2\n");
	}
	else // 중간 자식
	{
		dup2(fd->pipe[0][0], 0);
		dup2(fd->pipe[1][1], 1);
		close(fd->pipe[1][0]);
		close(fd->pipe[0][1]);
		if (execve("/bin/cat", aux->exec_param[0], NULL) == -1)
			printf("failed c1\n");
	}
}

void	execute_parent_process(t_aux *aux)
{
	wait(&aux->status);
}

void	init_struct(int argc, t_fd *fd, t_aux *aux)
{
	int	i;

	i = 0;
	fd->pipe = NULL;
	fd->infile = 0;
	fd->outfile = 0;
	fd->argc = argc;
	fd->pipe_num = argc - 3;
	aux->exec_param = NULL;
	aux->path = NULL;
	aux->str_infile = NULL;
	aux->argc = argc;
	aux->cmd_num = argc - 3;
	aux->fork_num = argc - 2;
	aux->status = 0;
	aux->pid = (pid_t *)ft_calloc(sizeof(pid_t), aux->fork_num);
	if (aux->pid == NULL)
		exit(EXIT_FAILURE);
	while (i < argc - 2)
	{
		aux->pid[i] = 1;
		i++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_fd	fd;
	t_aux	aux;

	if (argc < 5)
		exit(EXIT_FAILURE);
	init_struct(argc, &fd, &aux);
	parse_input(argv, &aux);
	open_files(argv, &fd);
	open_pipes(&fd);
	fork_child_process(&aux);
	if (check_child_process(&aux) == 1)
		execute_child_process(&fd, &aux);
	else
		execute_parent_process(&aux);
}