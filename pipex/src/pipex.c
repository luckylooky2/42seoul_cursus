/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:35:15 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 03:10:21 by chanhyle         ###   ########.fr       */
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
		if (aux->here_doc == 0)
			aux->exec_param[i] = ft_split(argv[i + 2], ' ');
		else
			aux->exec_param[i] = ft_split(argv[i + 3], ' ');
		if (aux->exec_param[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	add_path(aux, envp);
}

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

void	execute_first_child(char *envp[], t_fd *fd, t_aux *aux)
{
	char	*line;

	line = NULL;
	if (aux->here_doc == 0)
	{
		dup2(fd->infile, STDIN_FILENO);
		dup2(fd->pipe[0][1], STDOUT_FILENO);
		close_pipes(fd);
		if (execve(aux->path[0], aux->exec_param[0], envp) == -1)
		{
			if (aux->path[0][0] == '/')
				write(2, "no such file or directory: ", 28);
			else
				write(2, "command not found: ", 20);
			write(2, aux->path[0], ft_strlen(aux->path[0]));
			write(2, "\n", 1);
			if (aux->path[0][0] == '/')
				exit(EXIT_NO_FILE);
			else
				exit(EXIT_NO_COMMAND);
		}
	}
	else if (aux->here_doc == 1)
	{
		dup2(fd->pipe[0][1], STDOUT_FILENO);
		close_pipes(fd);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (line == NULL)
				exit(EXIT_FAILURE);
			if (check_limiter(aux, line) == 1)
			{
				free(line);
				break ;
			}
			write(STDOUT_FILENO, line, ft_strlen(line));
			free(line);
		}
		if (execve(aux->path[0], aux->exec_param[0], envp) == -1)
		{
			if (aux->path[0][0] == '/')
				write(2, "no such file or directory: ", 28);
			else
				write(2, "command not found: ", 20);
			write(2, aux->path[0], ft_strlen(aux->path[0]));
			write(2, "\n", 1);
			exit(EXIT_FAILURE);
		}
	}
}

void	execute_last_child(char *envp[], t_fd *fd, t_aux *aux)
{
	dup2(fd->pipe[fd->pipe_num - 1][0], STDIN_FILENO);
	dup2(fd->outfile, STDOUT_FILENO);
	close_pipes(fd);
	if (aux->here_doc == 0)
	{
		if (execve(aux->path[fd->pipe_num],
				aux->exec_param[fd->pipe_num], envp) == -1)
		{
			if (aux->path[fd->pipe_num][0] == '/')
				write(2, "no such file or directory: ", 28);
			else
				write(2, "command not found: ", 20);
			write(2, aux->path[fd->pipe_num], ft_strlen(aux->path[fd->pipe_num]));
			write(2, "\n", 1);
			if (aux->path[fd->pipe_num][0] == '/')
				exit(EXIT_NO_FILE);
			else
				exit(EXIT_NO_COMMAND);
		}
	}
	else
	{
		if (execve(aux->path[fd->pipe_num - 1],
			aux->exec_param[fd->pipe_num - 1], envp) == -1)
		{
			if (aux->path[fd->pipe_num - 1][0] == '/')
				write(2, "no such file or directory: ", 28);
			else
				write(2, "command not found: ", 20);
			write(2, aux->path[fd->pipe_num - 1], ft_strlen(aux->path[fd->pipe_num - 1]));
			write(2, "\n", 1);
			if (aux->path[fd->pipe_num - 1][0] == '/')
				exit(EXIT_NO_FILE);
			else
				exit(EXIT_NO_COMMAND);
		}
	}
}

void	execute_middle_child(char *envp[], t_fd *fd, t_aux *aux)
{
	int	nth;

	nth = check_nth_child_process(aux);
	dup2(fd->pipe[nth - 1][0], STDIN_FILENO);
	dup2(fd->pipe[nth][1], STDOUT_FILENO);
	close_pipes(fd);
	if (execve(aux->path[nth - 1], aux->exec_param[nth - 1], envp) == -1)
	{
		if (aux->path[nth - 1][0] == '/')
			write(2, "no such file or directory: ", 28);
		else
			write(2, "command not found: ", 20);
		write(2, aux->path[nth - 1], ft_strlen(aux->path[nth - 1]));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	execute_child_process(char *envp[], t_fd *fd, t_aux *aux)
{
	if (aux->pid[0] == 0)
		execute_first_child(envp, fd, aux);
	else if (aux->pid[aux->fork_num - 1] == 0)
		execute_last_child(envp, fd, aux);
	else
		execute_middle_child(envp, fd, aux);
}

void	execute_parent_process(t_aux *aux, t_fd *fd)
{
	pid_t	pid;
	pid_t	last_pid;
	
	pid = 0;
	if (aux->here_doc == 0)
		last_pid = aux->pid[aux->cmd_num - 1];
	else
		last_pid = aux->pid[aux->cmd_num];
	close_pipes(fd);
	while (pid != last_pid)
		pid = waitpid(last_pid, &aux->status, WNOHANG);
	exit(WEXITSTATUS(aux->status));
	// free_all
}

void	check_here_doc(char *argv[], t_aux *aux)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (ft_strlen(argv[1]) != 8)
	{
		aux->here_doc = 0;
		return ;
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		aux->here_doc = 1;
		return ;	
	}
	aux->here_doc = 0;
	return ;
}

void	init_struct(int argc, t_fd *fd, t_aux *aux)
{
	int	i;

	i = 0;
	fd->pipe = NULL;
	fd->infile = 0;
	fd->outfile = 0;
	fd->argc = argc;
	fd->pipe_num = argc - 4;
	aux->exec_param = NULL;
	aux->path = NULL;
	aux->argc = argc;
	aux->cmd_num = argc - 3;
	aux->fork_num = argc - 3;
	aux->limiter = NULL;
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

void	init_struct_here_doc(int argc, char *argv[], t_fd *fd, t_aux *aux)
{
	int	i;

	i = 0;
	fd->pipe = NULL;
	fd->infile = 0;
	fd->outfile = 0;
	fd->argc = argc;
	fd->pipe_num = argc - 4; // + 1
	aux->exec_param = NULL;
	aux->path = NULL;
	aux->argc = argc;
	aux->cmd_num = argc - 4;
	aux->fork_num = argc - 4; 
	aux->limiter = argv[2];
	aux->status = 0;
	aux->pid = (pid_t *)ft_calloc(sizeof(pid_t), aux->fork_num);
	if (aux->pid == NULL)
		exit(EXIT_FAILURE);
	while (i < argc - 3)
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
	check_here_doc(argv, &aux); // here_doc이 1일 경우, argc != 6인 경우 제외하기
	if (aux.here_doc == 0)
		init_struct(argc, &fd, &aux);
	else if (aux.here_doc == 1)
		init_struct_here_doc(argc, argv, &fd, &aux);
	parse_input(argv, envp, &aux);
	open_files(argv, &aux, &fd);
	open_pipes(&fd);
	fork_child_process(&aux);
	if (check_child_process(&aux) == 1)
		execute_child_process(envp, &fd, &aux);
	else
		execute_parent_process(&aux, &fd);
	exit(aux.status);
}
