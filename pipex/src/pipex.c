/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:35:15 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/05 17:46:24 by chanhyle         ###   ########.fr       */
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

int	find_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P')
			if (envp[i][1] == 'A')
				if (envp[i][2] == 'T')
					if (envp[i][3] == 'H')
						return (i);
		i++;
	}
	return (-1);
}

char	*join_path_cmd(t_aux *aux, char **path_ary, int i, int j)
{
	char	*tmp;

	tmp = NULL;
	if (j == 0)
		tmp = ft_strjoin(&(path_ary[j][5]), "/");
	else
		tmp = ft_strjoin(path_ary[j], "/");
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	tmp = ft_strjoin_free(&tmp, aux->exec_param[i][0], 0);
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	return (tmp);
}

void	access_path(t_aux *aux, char **path_ary)
{
	int i;
	int	j;
	char *tmp;

	i = 0;
	tmp = NULL;
	while (aux->exec_param[i])
	{
		j = 0;
		while (path_ary[j])
		{
			tmp = join_path_cmd(aux, path_ary, i, j);
			if (access(tmp, F_OK) == 0)
				aux->path[i] = tmp;
			else
				free(tmp);
			j++;
		}
		i++;
	}
}

void	add_path(t_aux *aux, char *envp[])
{
	int		path_num;
	char	**path_ary;
	int		i;

	i = 0;
	path_num = find_path(envp);
	if (path_num == -1)
		return ;
	path_ary = ft_split(envp[path_num], ':');
	if (path_ary == NULL)
		exit(EXIT_FAILURE);
	access_path(aux, path_ary);
	// printf("%s\n", aux->path[0]);
	// printf("%s\n", aux->path[1]);
	// printf("%s\n", aux->path[2]);
	// printf("%s\n", aux->path[3]);
	while (path_ary[i])
	{
		free(path_ary[i]);
		i++;
	}
	free(path_ary);
}

void	parse_input(char *argv[], char *envp[], t_aux *aux)
{
	int	i;

	i = 0;
	aux->exec_param = (char ***)ft_calloc(sizeof(char **), aux->cmd_num + 1);
	aux->path = (char **)ft_calloc(sizeof(char *), aux->cmd_num + 1);
	if (aux->exec_param == NULL || aux->path == NULL)
		exit(EXIT_FAILURE);
	while (i < aux->cmd_num)
	{
		aux->exec_param[i] = ft_split(argv[i + 2], ' ');
		if (aux->exec_param[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	add_path(aux, envp);
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

void	execute_child_process(t_fd *fd, t_aux *aux)
{
	if (aux->pid[0] == 0) // 첫 번째 자식
	{
		dup2(fd->pipe[0][1], STDOUT_FILENO);
		close(fd->pipe[0][0]);
		close(fd->pipe[1][0]);
		close(fd->pipe[1][1]);
		while (1)
		{
			aux->str_infile = get_next_line(fd->infile);
			if (aux->str_infile == NULL)
				break ;
			write(1, aux->str_infile, ft_strlen(aux->str_infile));
		}
	}
	else if (aux->pid[aux->fork_num - 1] == 0)// 마지막 자식
	{
		dup2(fd->pipe[1][0], 0);
        dup2(fd->outfile, 1);
        close(fd->pipe[1][1]);
        close(fd->pipe[0][0]);
        close(fd->pipe[0][1]);
        if (execve(aux->path[1], aux->exec_param[1], NULL) == -1)
            printf("failed c2\n");
	}
	else // 중간 자식
	{
		dup2(fd->pipe[0][0], 0);
		dup2(fd->pipe[1][1], 1);
		close(fd->pipe[1][0]);
		close(fd->pipe[0][1]);
		if (execve(aux->path[0], aux->exec_param[0], NULL) == -1)
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
	parse_input(argv, envp, &aux);
	open_files(argv, &fd);
	open_pipes(&fd);
	fork_child_process(&aux);
	if (check_child_process(&aux) == 1)
		execute_child_process(&fd, &aux);
	else
		execute_parent_process(&aux);
}