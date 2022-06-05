/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:35:15 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/06 00:38:15 by chanhyle         ###   ########.fr       */
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
						if (envp[i][4] == '=')
							return (i);
		i++;
	}
	return (-1);
}

char	*join_path_cmd(t_aux *aux, char **path_ary, int i, int j)
{
	char	*path;

	path = NULL;
	// if (aux->exec_param[i][0][0] == '/')
	// {
	// 	path = ft_strdup(aux->exec_param[i][0]);
	// 	if (path == NULL)
	// 		exit(EXIT_FAILURE);
	// 	return (path);
	// }
	if (j == 0)
		path = ft_strjoin(&(path_ary[j][5]), "/");
	else
		path = ft_strjoin(path_ary[j], "/");
	if (path == NULL)
		exit(EXIT_FAILURE);
	path = ft_strjoin_free(&path, aux->exec_param[i][0], 0);
	if (path == NULL)
		exit(EXIT_FAILURE);
	return (path);
}

int	check_access(t_aux *aux, char *path, int i, int nth)
{
	if (nth == 1)
	{
		if (access(aux->exec_param[i][0], F_OK) == 0)
		{
			aux->path[i] = ft_strdup(aux->exec_param[i][0]);
			return (0);
		}
	}
	else if (nth == 2)
	{
		if (access(path, F_OK) == 0)
		{
			aux->path[i] = path;
			return (0);
		}
	}
	return (-1);
}

void	access_path(t_aux *aux, char **path_ary, int path_num)
{
	int		i;
	int		j;
	char	*path;

	i = -1;
	path = NULL;
	while (aux->exec_param[++i])
	{
		j = -1;
		while (path_ary[++j])
		{
			if (check_access(aux, path, i, 1) == 0
				|| aux->exec_param[i][0][0] == '/')
				break ;
			path = join_path_cmd(aux, path_ary, i, j);
			if (check_access(aux, path, i, 2) == 0)
				break ;
			free(path);
		}
		if (j == path_num || aux->exec_param[i][0][0] == '/')
			aux->path[i] = ft_strdup(aux->exec_param[i][0]);
		if (aux->path[i] == NULL)
			exit(EXIT_FAILURE);
	}
}

void	add_path(t_aux *aux, char *envp[])
{
	char	**path_ary;
	int		path_loc;
	int		path_num;
	int		i;

	i = 0;
	path_num = 0;
	path_loc = find_path(envp);
	if (path_loc == -1)
		exit(EXIT_FAILURE);
	path_ary = ft_split(envp[path_loc], ':');
	if (path_ary == NULL)
		exit(EXIT_FAILURE);
	while (path_ary[path_num])
		path_num++;
	access_path(aux, path_ary, path_num);
	while (path_ary[i]) // free path_ary
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
	if (fd->infile < 0)
	{
		write(2, "fail\n", 6);
		// perror(); //zsh: no such file or directory: file
		// exit(EXIT_FAILURE);
	}
	fd->outfile = open(argv[fd->argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd->outfile < 0)
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

void	fork_child_process(t_aux *aux)
{
	int	i;

	i = 1;
	aux->pid[0] = fork();
	if (aux->pid[0] == -1)
		exit(EXIT_FAILURE);
	while (i < aux->fork_num)
	{
		if (check_child_process(aux) == 0)
			aux->pid[i] = fork();
		if (aux->pid[i] == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	close_pipes_first(t_fd *fd)
{
	int	i;

	i = 1;
	close(fd->pipe[0][0]);
	while (i < fd->pipe_num)
	{
		close(fd->pipe[i][0]);
		close(fd->pipe[i][1]);
		i++;
	}
}

void	execute_first_child(t_fd *fd, t_aux *aux)
{
	char	*line;

	line = NULL;
	dup2(fd->pipe[0][1], STDOUT_FILENO);
	close_pipes_first(fd);
	while (1)
	{
		line = get_next_line(fd->infile);
		if (line == NULL)
			break ;
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
	}
}

void	close_pipes_last(t_fd *fd)
{
	int	i;

	i = 0;
	close(fd->pipe[fd->pipe_num - 1][1]);
	while (i < fd->pipe_num - 1)
	{
		close(fd->pipe[i][0]);
		close(fd->pipe[i][1]);
		i++;
	}
}

void	execute_last_child(t_fd *fd, t_aux *aux)
{
	dup2(fd->pipe[aux->cmd_num - 1][0], STDIN_FILENO);
	dup2(fd->outfile, STDOUT_FILENO);
	close_pipes_last(fd);
	if (execve(aux->path[fd->pipe_num - 1],
			aux->exec_param[fd->pipe_num - 1], NULL) == -1)
	{
		write(2, "failed c2\n", 11);
		// why? 1번에다가 쓰는게 아니기 때문
		// perror(); //zsh: command not found: ca
		// 명령어 옵션은 새로운 프로세스에서 판단함
	}
}

void	close_pipes_middle(t_fd *fd, int nth_child)
{
	int	i;

	i = 0;
	close(fd->pipe[nth_child][0]);
	close(fd->pipe[nth_child -1][1]);
	while (i < nth_child - 1)
	{
		close(fd->pipe[i][0]);
		close(fd->pipe[i][1]);
		i++;
	}
	i = nth_child + 1;
	while (i < fd->pipe_num)
	{
		close(fd->pipe[i][0]);
		close(fd->pipe[i][1]);
		i++;
	}
}

void	execute_middle_child(t_fd *fd, t_aux *aux)
{
	int	nth_child;

	if (fd->infile < 0)
		exit(EXIT_FAILURE);
	nth_child = check_nth_child_process(aux);
	dup2(fd->pipe[nth_child - 1][0], STDIN_FILENO);
	dup2(fd->pipe[nth_child][1], STDOUT_FILENO);
	close_pipes_middle(fd, nth_child);
	if (execve(aux->path[nth_child - 1],
			aux->exec_param[nth_child - 1], NULL) == -1)
	{
		write(2, "failed c1\n", 11);
		// why? 1번에다가 쓰는게 아니기 때문
		// perror(); //zsh: command not found: ca
	}
}

void	execute_child_process(t_fd *fd, t_aux *aux)
{
	// printf("pid : %d\n", aux->pid[0]);
	if (aux->pid[0] == 0)
		execute_first_child(fd, aux);
	else if (aux->pid[aux->fork_num - 1] == 0)
		execute_last_child(fd, aux);
	else
		execute_middle_child(fd, aux);
}

void	execute_parent_process(t_aux *aux)
{
	wait(&aux->status);
	// free_all
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

int	main(int argc, char *argv[], char *envp[])
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
