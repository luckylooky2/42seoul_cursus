/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:35:15 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/03 15:40:56 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// $> ./pipex infile ``ls -l'' ``wc -l'' outfile

int	free_c_params(t_data **data)
{
	int	i;

	i = 0;
	if ((*data)->c1_param != NULL)
	{
		while ((*data)->c1_param[i])
		{
			free((*data)->c1_param[i]);
			i++;
		}
		free((*data)->c1_param);
	}
	i = 0;
	if ((*data)->c2_param != NULL)
	{
		while ((*data)->c2_param[i])
		{
			free((*data)->c2_param[i]);
			i++;
		}
		free((*data)->c2_param);
	}
	return (0);
}

int	check_input(int argc, char *argv[], t_data *data)
{
	if (argc != 5)
		return (0);
	data->c1_param = ft_split(argv[2], ' ');
	data->c2_param = ft_split(argv[3], ' ');
	if (data->c1_param == NULL || data->c2_param == NULL)
		return (free_c_params(&data));
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	pid_t pid = 1;
    pid_t pid2 = 1;
    pid_t pid3 = 1;
	int status;
    int fd[2];
    int fd2[2];
	pid_t res;
	int fd_file1;
	int fd_file2;
	char *tmp;

	fd_file1 = open(argv[1], O_RDONLY);
	fd_file2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (check_input(argc, argv, &data) == 0)
		exit(EXIT_FAILURE);
	pipe(fd);
	pipe(fd2);
	pid = fork();
    if (pid != 0 && pid2 != 0)
        pid2 = fork();
    if (pid != 0 && pid2 != 0)
        pid3 = fork();
	if (pid == 0) // 자식 1
	{
		int i = 0;
		tmp = get_next_line(fd_file1);
		dup2(fd[1], 1);
        close(fd[0]);
        close(fd2[0]);
        close(fd2[1]);
		write(1, tmp, ft_strlen(tmp));
	}
	if (pid2 == 0) // 자식 2
    {
		dup2(fd[0], 0);
		dup2(fd2[1], 1);
        close(fd2[0]);
		close(fd[1]);
		if (execve("/bin/cat", data.c1_param, NULL) == -1)
			printf("failed c1\n");
    }
	else if (pid3 == 0) // 자식 3
    {
		dup2(fd2[0], 0);
        dup2(fd_file2, 1);
        close(fd2[1]);
        close(fd[0]);
        close(fd[1]);
        if (execve("/usr/bin/wc", data.c2_param, NULL) == -1)
            printf("failed c2\n");
    }
    else // 부모
		wait(&status);
}