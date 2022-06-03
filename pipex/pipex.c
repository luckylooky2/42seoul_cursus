/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:35:15 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/03 08:33:57 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// $> ./pipex infile ``ls -l'' ``wc -l'' outfile

typedef struct s_data
{
	char **c1_param;
	char **c2_param;
}	t_data;

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(nmemb * size);
	if (!new_str)
		return (NULL);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)new_str)[i++] = 0;
		return (new_str);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	if (s == NULL)
		return (0);
	while (s[cnt])
		cnt++;
	return (cnt);
}

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
	pid_t pid;
    pid_t pid2;
	int status;
    int fd[2];
    int fd2[2];
	pid_t res;
	int fd_file1;
	int exe_res;
	char *tmp;

	fd_file1 = open(argv[1], O_RDONLY);
	if (check_input(argc, argv, &data) == 0)
		exit(EXIT_FAILURE);
	pipe(fd);
	pipe(fd2);
	pid = fork();
    if (pid != 0)
        pid2 = fork();
	if (pid == 0) // 자식 1
    {
		// dup2(fd2[1], 1);
		// close(fd2[0]);
        dup2(fd[0], fd_file1);
        close(fd[1]);
        // execve("/usr/bin/wc", b, NULL);
		execve("/bin/cat", data.c1_param, NULL);
    }
	else if (pid2 == 0) // 자식 2
    {
        dup2(fd[1], 1);
        close(fd[0]);
		// close(fd2[0]);
		// close(fd2[1]);
        if (execve("/bin/cat", data.c2_param, NULL) == -1)
            printf("no cat\n");
    }
    else // 부모
    {
		// dup2(fd2[0], fd_file1);
		// close(fd2[1]);
		// while (1)
		// {
		// 	tmp = get_next_line(fd_file1);
		// 	printf("%s", tmp);
		// 	if (tmp == NULL)
		// 		break ;
		// 	write(fd2[0], tmp, ft_strlen(tmp));
		// }
		// close(fd[0]);
		// close(fd[1]);
        res = waitpid(pid2, &status, 0); // 대기
		// printf("status : %d\n", WEXITSTATUS(status));
        // res = waitpid(pid, &status, 0); // 대기
		// printf("res : %d\n", res);
		// printf("status : %d\n", WEXITSTATUS(status));
    }
}