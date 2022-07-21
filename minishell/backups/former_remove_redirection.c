/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:16:09 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/15 16:37:32 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_data
{
	int		argc;
	int		infile_num;
	int		outfile_num;
	char	**rd_flag;
	char	check;
	char	**cmd;
	int		cmd_num;
	int		next_flag;
	int		tmp;
	int		i;
	int		j;
}	t_data;

void	print_in(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("%d %d\n", data->infile_num, data->outfile_num);
	while (data->rd_flag[i])
	{
		j = 0;
		while (data->rd_flag[i][j])
		{
			printf("%c ", data->rd_flag[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	print_file(char **file)
{
	int	i;

	i = 0;
	while (file[i])
		printf("%s\n", file[i++]);
}

int	return_index_single(char *str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
}

int	check_naming_rule(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '\0')
		return (1);
	return (0);
}

char	check_error(char **command, int i, int j, t_data *data)
{
	if (command[i][j + 1] == command[i][j])
	{
		if (check_naming_rule(command[i][j + 2]) == 0)
			exit(printf("EXIT_FAILURE"));
		else if (command[i][j + 2] == '\0')
		{
			if (command[i + 1] == NULL)
				exit(printf("EXIT_FAILURE"));
		}
		if (command[i][j] == '<')
			return ('2');
		return ('4');
	}
	else if (check_naming_rule(command[i][j + 1]) == 0)
		exit(printf("EXIT_FAILURE"));
	else if (command[i][j + 1] == '\0')
	{
		if (command[i + 1] == NULL)
			exit(printf("EXIT_FAILURE"));
	}
	if (command[i][j] == '<')
		return ('1');
	return ('3');
}

void	check_error_next_line(char **command, int i, t_data *data)
{
	int	j;

	j = ft_strlen(command[i]);
	if (command[i][j - 1] == '<' || command[i][j - 1] == '>')
	{
		if (check_naming_rule(command[i + 1][0]) == 0)
			exit(printf("EXIT_FAILURE"));
		else
			data->check = data->rd_flag[i][j - 1];
	}
}

void	increase_file_num(t_data *data, int i, int j)
{
	data->rd_flag[i][j] = data->check;
	if (data->check == '2' || data->check == '4')
		data->rd_flag[i][j++ + 1] = data->check;
	if (data->check == '1' || data->check == '2')
		data->infile_num++;
	else
		data->outfile_num++;
}

void	assign_rd_flag(char **command, int i, t_data *data, int ***stat)
{
	int	j;

	j = 0;
	while (command[i][j])
	{
		if ((command[i][j] == '<' || command[i][j] == '>')
			&& (*stat)[i][j] == -1)
		{
			data->check = check_error(command, i, j, data);
			if (data->check != '9')
				increase_file_num(data, i, j);
		}
		if (i > 0 && j == 0
			&& (*stat)[i - 1][return_index_single(data->rd_flag[i - 1]) - 1]
			!= -1)
			data->check = '9';
		else
			data->rd_flag[i][j] = data->check;
		j++;
	}
	data->check = '9';
}

char	*return_bracket(char *start, int *stat)
{
	if (start == NULL)
		return (NULL);
	while (*start)
	{
		if (((*start == '<' || *start == '>') && *stat == -1) || *start == '\0')
			return ((char *)start);
		++start;
		++stat;
	}
	return ((char *)start);
}

int	return_index(char **str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
}

void	calculate_cmd_num(t_data *data)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	while (data->rd_flag[i])
	{
		j = 0;
		while (data->rd_flag[i][j])
		{
			if (data->rd_flag[i][j] == '9')
				data->cmd_num++;
			break ;
		}
		i++;
	}
}

void	free_command(char ***command)
{
	int	i;

	i = 0;
	while ((*command)[i])
		free((*command)[i++]);
	free(*command);
}

void	do_case_command(char **command, int **stat, t_data *data)
{
	char	*ptr;

	ptr = return_bracket(&command[data->i][data->j], &stat[data->i][data->j]);
	data->cmd[return_index(data->cmd)] = ft_substr(&command[data->i][data->j],
			0, (ptr - &command[data->i][data->j]));
	data->j = ft_strlen(data->cmd[return_index(data->cmd) - 1]) - 1;
}

int	join_redirection_and_file(char **command, char ***input,
	char ***output, int **stat, t_data *data)
{
	char	*ptr;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(&command[data->i][data->j], 0,
			(ptr - &command[data->i][data->j]));
	ptr = return_bracket(&command[data->i + 1][0], &stat[data->i + 1][0]);
	tmp2 = ft_substr(&command[data->i + 1][0], 0,
			(ptr - &command[data->i + 1][0]));
	data->tmp = ptr - &command[data->i + 1][0];
	ptr = ft_strjoin(tmp1, tmp2);
	if (*ptr == '<')
		(*input)[return_index(*input)] = ptr;
	else
		(*output)[return_index(*output)] = ptr;
	free(tmp1);
	free(tmp2);
	data->next_flag = 1;
	return (0);
}

void	cut_redirection_and_file(char **command, char ***input,
	char ***output, int **stat, t_data *data)
{
	char	*ptr;

	if (command[data->i][data->j + 1] == '<' ||
		command[data->i][data->j + 1] == '>')
		ptr = return_bracket(&command[data->i][data->j + 2],
				&stat[data->i][data->j + 2]);
	else
		ptr = return_bracket(&command[data->i][data->j + 1],
				&stat[data->i][data->j + 1]);
	ptr = ft_substr(&command[data->i][data->j], 0,
			(ptr - &command[data->i][data->j]));
	if (*ptr == '<')
		(*input)[return_index(*input)] = ptr;
	else
		(*output)[return_index(*output)] = ptr;
	data->j = data->j + ft_strlen(ptr) - 1;
}

int	do_case_redirection(char **command, char ***input,
	char ***output, int **stat, t_data *data)
{
	char	*ptr;

	if (command[data->i][data->j + 1] == '<' ||
		command[data->i][data->j + 1] == '>')
		ptr = return_bracket(&command[data->i][data->j + 2],
				&stat[data->i][data->j + 2]);
	else
		ptr = return_bracket(&command[data->i][data->j + 1],
				&stat[data->i][data->j + 1]);
	if (*ptr == '\0' && data->argc != data->i + 1
		&& (data->rd_flag)[data->i + 1][0] != '9')
		return (join_redirection_and_file(command, input, output, stat, data));
	else
		cut_redirection_and_file(command, input, output, stat, data);
	return (1);
}

void	set_start_index_j(t_data *data)
{
	if (data->next_flag == 0)
		data->j = 0;
	else
	{
		data->j = data->tmp;
		data->next_flag = 0;
	}
}

void	parse_redirection(char ***command, char ***input,
	char ***output, t_data *data, int ***stat)
{
	char	*ptr;

	*input = (char **)calloc(sizeof(char *), (data->infile_num + 1));
	*output = (char **)calloc(sizeof(char *), (data->outfile_num + 1));
	data->cmd = (char **)calloc(sizeof(char *), (data->cmd_num + 1));
	if (!(*input) || !(*output) || !(data->cmd))
		exit(printf("EXIT_FAILURE"));
	while ((data->rd_flag)[data->i])
	{
		set_start_index_j(data);
		while ((data->rd_flag)[data->i][data->j])
		{
			if ((data->rd_flag)[data->i][data->j] == '9')
				do_case_command(*command, *stat, data);
			else
			{
				if (do_case_redirection(*command, input,
						output, *stat, data) == 0)
					break ;
			}
			data->j++;
		}
		data->i++;
	}
}

void	init_data(char **str, t_data *data)
{
	int	i;

	i = 0;
	data->infile_num = 0;
	data->outfile_num = 0;
	data->check = '9';
	data->cmd_num = 0;
	data->next_flag = 0;
	data->tmp = 0;
	data->i = 0;
	data->j = 0;
	data->argc = return_index(str);
	data->rd_flag = (char **)calloc(sizeof(char *), data->argc + 1);
	while (i < data->argc)
	{
		data->rd_flag[i] = (char *)calloc(sizeof(char), ft_strlen(str[i]));
		ft_memset(data->rd_flag[i], '9', ft_strlen(str[i]));
		i++;
	}
}

void	free_rd_flag(t_data *data)
{
	int	i;

	i = 0;
	while (data->rd_flag[i])
		free(data->rd_flag[i++]);
	free(data->rd_flag);
}

void	remove_redirection(char ***command, char ***input,
		char ***output, int ***stat)
{
	t_data	data;
	int		i;

	i = 0;
	init_data(*command, &data);
	while ((*command)[i])
	{
		assign_rd_flag(*command, i, &data, stat);
		check_error_next_line(*command, i, &data);
		i++;
	}
	calculate_cmd_num(&data);
	parse_redirection(command, input, output, &data, stat);
	free_rd_flag(&data);
	// free_command(command);
	// *command = data->cmd;
}

void	malloc_str(char ***str)
{
	*str = (char **)calloc(sizeof(char *), 100);
	// (*str)[0] = "cat";
	// (*str)[1] = "<";
	// (*str)[2] = "file1";
	// (*str)[3] = "<";
	// (*str)[4] = "file2";
	(*str)[0] = "cat<s>d>a>>sd>>_1<2<3>"; // redirection으로 끝나면 무조건 다음 포인터는 1~4
	(*str)[1] = "Makefile>";
	(*str)[2] = "asd>as>a";	
	(*str)[3] = "asd>as>a";
	(*str)[4] = "asd>as>a";
}

void	malloc_stat(char **str, int ***stat)
{
	int cnt;
	int	i;
	int	j;

	cnt = 0;
	i = 0;
	*stat = (int **)calloc(sizeof(int *), (return_index(str) + 1));
	while (i < return_index(str))
	{
		cnt = return_index_single(str[i]);
		j = 0;
		(*stat)[i] = (int *)calloc(sizeof(int), cnt);
		while (j < cnt)
		{
			(*stat)[i][j] = -1;
			j++;
		}
		i++;
	}
	(*stat)[0][3] = 0;
	(*stat)[0][4] = 0;
	(*stat)[1][8] = 0;
	(*stat)[2][3] = 0;
	(*stat)[2][4] = 0;
	(*stat)[2][5] = 0;
	(*stat)[2][6] = 0;
	(*stat)[2][7] = 0;
}

int	main(void)
{
	int		**stat;
	char	**str;
	char	**input;
	char	**output;


	malloc_str(&str);
	malloc_stat(str, &stat);
	remove_redirection(&str, &input, &output, &stat);
	// print_file(input);
	// printf("----------------\n");
	// print_file(output);
	// system("leaks a.out");
}

// 9 : command
// 1 : <
// 2 : <<
// 3 : >
// 4 : >>