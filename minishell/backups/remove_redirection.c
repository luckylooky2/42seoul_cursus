/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 14:22:51 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/17 01:35:51 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_data
{
	int		infile_num;
	int		outfile_num;
	int		cmd_num;
	char	*rd_flag;
	char	check;
	int		next_flag;
	int		tmp;
}	t_data;

void	print_in(t_data *data)
{
	int	i;

	i = 0;
	printf("%d %d\n", data->infile_num, data->outfile_num);
	while (data->rd_flag[i])
	{
		printf("%c", data->rd_flag[i]);
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

void	print_deque(t_deq *deque)
{
	int	i;

	i = 0;
	deque->tail = deque->tail->next;
	while (i < deque->size)
	{
		printf("%s\n", (char *)deque->tail->data);
		deque->tail = deque->tail->next;
		i++;
	}
}

int	return_last_index(char **str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
}

void	init_data(char *cmd_line, t_data *data)
{
	int	len;

	len = ft_strlen(cmd_line);
	if (len == 0)
		return ;
	data->infile_num = 0;
	data->outfile_num = 0;
	data->check = '0';
	data->cmd_num = 0;
	data->next_flag = 0;
	data->tmp = 0;
	data->rd_flag = (char *)ft_calloc(sizeof(char), len);
	if (data->rd_flag == NULL)
		exit(printf("EXIT_FAILURE"));
	ft_memset(data->rd_flag, '0', len);
}

void	init_parsed(t_command *parsed, t_data *data)
{
	parsed->command = (char **)ft_calloc(sizeof(char *), data->cmd_num + 1);
	parsed->input = ft_deq_new();
	parsed->output = ft_deq_new();
}

void	calculate_cmd_num(t_data *data)
{
	int	i;

	i = 0;
	while (data->rd_flag[i])
	{
		if (data->rd_flag[i] == '0')
		{
			data->cmd_num++;
			while (data->rd_flag[i] != ' ')
				i++;
		}
		else
			i++;
		while (data->rd_flag[i] == ' ')
			i++;
	}
}

int		skip_space(char *cmd_line, char *intprt, int i, t_data *data)
{
	i++;
	while (cmd_line[i] == ' ' && intprt[i] == '1')
	{
		data->rd_flag[i] = ' ';
		i++;
	}
	return (i);
}

void	check_case_end(char *cmd_line, char *intprt, int i, t_data *data)
{
	int	new_i;

	new_i = skip_space(cmd_line, intprt, i, data);
	if (cmd_line[new_i] == '\0')
	{
		printf("i : %d 1\n", i);
		exit(printf("EXIT_FAILURE"));
	}
}

void	check_case_next_token(char *cmd_line, char *intprt, int i, t_data *data)
{
	int	new_i;
	int	skip_flag;

	skip_flag = 0;
	new_i = skip_space(cmd_line, intprt, i, data);
	if (new_i - 1 == i)
		skip_flag = 1;
	if ((cmd_line[new_i] == '<' || cmd_line[new_i] == '>')
		&& intprt[new_i] == '1' && skip_flag == 0)
	{
			printf("i : %d 2\n", i);
		exit(printf("EXIT_FAILURE"));
	}
}

void	check_case_not_redirection(char *cmd_line, char *intprt, int i)
{
	if (intprt[i + 1] == '1')
	{
		if (cmd_line[i + 1] == '!' || cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>')
		{
			printf("i : %d 3\n", i);
			exit(printf("EXIT_FAILURE"));
		}
	}
}

void	check_error(char *cmd_line, char *intprt, int i, t_data *data)
{
	if (cmd_line[i + 1] == cmd_line[i] && intprt[i + 1] == '1')
		i++;
	check_case_end(cmd_line, intprt, i, data);
	check_case_next_token(cmd_line, intprt, i, data);
	check_case_not_redirection(cmd_line, intprt, i);
}

void	assign_check(char *cmd_line, char *intprt, int i, t_data *data)
{
	if (cmd_line[i] == cmd_line[i + 1] && intprt[i + 1] == '1')
	{
		if (cmd_line[i] == '<')
			data->check = '2';
		else
			data->check = '4';
	}
	else if ((cmd_line[i] == cmd_line[i + 1] && intprt[i + 1] == '0') || (cmd_line[i] != cmd_line[i + 1]))
	{
		if (cmd_line[i] == '<')
			data->check = '1';
		else
			data->check = '3';
	}
}

void	check_assign_rd_flag(char *cmd_line, char *intprt, int *i, t_data *data)
{
	int	skip;
	
	data->rd_flag[*i] = data->check;
	if (data->check == '2' || data->check == '4')
		data->rd_flag[++(*i)] = data->check;
	skip = skip_space(cmd_line, intprt, *i, data);
	if (skip - 1 == *i)
	{
		(*i)++;
		while (!((cmd_line[*i] == '<' || cmd_line[*i] == '>' 
			|| cmd_line[*i] == ' ') && intprt[*i] == '1' || cmd_line[*i] == '\0'))
		{
			data->rd_flag[*i] = data->check;
			(*i)++;
		}
		(*i)--;
		data->check = '0';
	}
	else
	{
		while (!((cmd_line[skip] == '<' || cmd_line[skip] == '>' 
			|| cmd_line[skip] == ' ') && intprt[skip] == '1' || cmd_line[skip] == '\0'))
		{
			data->rd_flag[skip] = data->check;
			(skip)++;
		}
		skip--;
		data->check = '0';
		*i = skip;
	}
}

void	increase_file_num(char *cmd_line, int i, t_data *data)
{
	if (cmd_line[i] == '<')
		data->infile_num++;
	else
		data->outfile_num++;
}

void	assign_rd_flag(char *cmd_line, char *intprt, t_data *data)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if ((cmd_line[i] == '<' || cmd_line[i] == '>') && intprt[i] == '1')
		{
			check_error(cmd_line, intprt, i, data);
			increase_file_num(cmd_line, i, data);
			assign_check(cmd_line, intprt, i, data);
			check_assign_rd_flag(cmd_line, intprt, &i, data);
		}
		else if (cmd_line[i] == ' ' && intprt[i] == '1')
			data->rd_flag[i] = ' ';
		else
			data->rd_flag[i] = data->check;
		i++;
	}
}

int	return_end_index(char *start, int i)
{
	char	rd_flag;

	rd_flag = start[i];
	while (start[i])
	{
		if (start[i] != rd_flag)
			return (i);
		i++;
	}
	return (i);
}

int	return_end_index_without_space(char *start, int i, int *space_flag)
{
	char	rd_flag;

	rd_flag = start[i];
	while (start[i])
	{
		if (start[i] != rd_flag)
			break ;
		i++;
	}
	if (start[i] == ' ')
	{
		*space_flag = 1;
		i++;
		while (start[i] == ' ')
			i++;
	}
	if (rd_flag != start[i])
		*space_flag = 0;
	else
	{
		while (start[i])
		{
			if (start[i] != rd_flag)
				break ;
			i++;
		}
	}
	return (i);
}

int	do_case_command(char *cmd_line, int i, t_data *data, t_command *parsed)
{
	int	end;

	end = return_end_index(data->rd_flag, i);
	parsed->command[return_last_index(parsed->command)] = ft_substr(&cmd_line[i], 0, end - i);
	return (end);
}

int	skip_character(char *start, int i, char ch)
{
	while (start[i] == ch || start[i] == '\0')
		i++;
	return (i);
}

void	join_redirection_and_file(char *cmd_line, int i, t_data *data, t_command *parsed)
{
	int		end;
	int		space_idx;
	char	*tmp1;
	char	*tmp2;
	char	*join;

	end = return_end_index_without_space(data->rd_flag, i, &space_idx);
	space_idx = skip_character(data->rd_flag, i, data->rd_flag[i]) + 1;
	tmp1 = ft_substr(&cmd_line[i], 0, space_idx - i);
	space_idx = skip_character(data->rd_flag, space_idx, ' ');
	tmp2 = ft_substr(&cmd_line[space_idx], 0, end - space_idx);
	if (tmp1 == NULL || tmp2 == NULL)
		exit(printf("EXIT_FAILURE"));
	join = ft_strjoin(tmp1, tmp2);
	if (join == NULL)
		exit(printf("EXIT_FAILURE"));
	if (cmd_line[i] == '<')
		ft_deq_push_back(parsed->input, join);
	else
		ft_deq_push_back(parsed->output, join);
	free(tmp1);
	free(tmp2);
}

void	cut_redirection_and_file(char *cmd_line, int i, t_data *data, t_command *parsed)
{
	int		end;
	char	*tmp;
	char	*join;

	end = return_end_index(data->rd_flag, i);
	tmp = ft_substr(&cmd_line[i], 0, end - i);
	if (tmp == NULL)
		exit(printf("EXIT_FAILURE"));
	if (data->rd_flag[i] == '1')
		join = ft_strjoin("< ", &tmp[1]);
	else if (data->rd_flag[i] == '2')
		join = ft_strjoin("<< ", &tmp[2]);
	else if (data->rd_flag[i] == '3')
		join = ft_strjoin("> ", &tmp[1]);
	else if (data->rd_flag[i] == '4')
		join = ft_strjoin(">> ", &tmp[2]);
	if (join == NULL)
		exit(printf("EXIT_FAILURE"));
	if (cmd_line[i] == '<')
		ft_deq_push_back(parsed->input, join);
	else
		ft_deq_push_back(parsed->output, join);
	free(tmp);
}

int	do_case_redirection(char *cmd_line, int i, t_data *data, t_command *parsed)
{
	char	rd_flag;
	int		space_flag;
	int		end;

	rd_flag = data->rd_flag[i];
	space_flag = 0;
	end = return_end_index_without_space(data->rd_flag, i, &space_flag);
	// printf("i : %d, %c, end : %d, %c\n", i, cmd_line[i], end, cmd_line[end]);
	// printf("%d\n", space_flag);
	if (space_flag == 1)
		join_redirection_and_file(cmd_line, i, data, parsed);
	else
		cut_redirection_and_file(cmd_line, i, data, parsed);
	return (end);
}

void	parse_redirection(char *cmd_line, t_data *data, t_command *parsed)
{
	int		i;

	i = 0;
	while ((data->rd_flag)[i])
	{
		if ((data->rd_flag)[i] == '0')
			i = do_case_command(cmd_line, i, data, parsed);
		else if ((data->rd_flag)[i] != ' ')
			i = do_case_redirection(cmd_line, i, data, parsed);
		else
			i++;
	}
}

void	remove_redirection(char *cmd_line, char *intprt)
{
	t_data		data;
	t_command	parsed;

	init_data(cmd_line, &data);
	assign_rd_flag(cmd_line, intprt, &data);
	calculate_cmd_num(&data);
	init_parsed(&parsed, &data);
	parse_redirection(cmd_line, &data, &parsed);
	print_in(&data);
	print_file(parsed.command);
	print_deque(parsed.input);
	print_deque(parsed.output);
	free(data.rd_flag);
	// system("leaks a.out");
	// return (parsed);
}


void	malloc_intprt(char **intprt, int len)
{
	*intprt = (char *)ft_calloc(sizeof(char), len);
	ft_memset(*intprt, '1', len);
	// (*intprt)[3] = '0';
	(*intprt)[4] = '0';
	(*intprt)[19] = '0';
}

int	main(void)
{
	char	*cmd_line;
	char	*intprt;
	int		len;

	cmd_line = "  >>>file1 cat<   s >a>>_1 Makefile<<aaa asd>>as<a -a -a";
	// cmd_line = "   < file1 cat > file2     ";
	// cmd_line = "";
	len = ft_strlen(cmd_line);
	malloc_intprt(&intprt, len);
	remove_redirection(cmd_line, intprt);
}

// input char *cmd_line
// input char *interpret
// output t_command	*parsed