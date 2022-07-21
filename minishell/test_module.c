/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_module.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:45:06 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/19 18:57:46 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*count_arr_len(char **arr, int *n)
{
	char **temp = arr;

	*n = 0;
	while (*temp[*n])
		(*n)++;
	int *res = malloc(sizeof(int) * *n);
	for (int i = 0; i < *n; i++)
		res[i] = ft_strlen(arr[i]);
	return (res);
}

void	print_fd_status(int n, int fd, int flag)
{
	struct stat stat;

	fstat(fd, &stat);
	if (flag == READ)
		printf("\033[0;31mPIPE %d READ COUNT: %d\033[0m\n", n, fd);
	else if (flag == WRITE)
		printf("\033[0;31mPIPE %d WRITE COUNT: %d\033[0m\n", n, fd);
}

void	print_debug_message(char *str)
{
	printf("\033[0;31m%s\033[0m\n", str);
}

void	print_parsed_arg(t_deq *parsed_arg)
{
	t_deq	*linked_commands;
	t_gnode	*cur_arg;
	t_gnode	*cur_lcmd;
	t_commands	*commands;
	int		i = 0;
	int		j = 0;

	cur_arg = parsed_arg->tail->next;
	while (cur_arg != parsed_arg->tail)
	{
		printf("\033[0;31m===PARSED     ARGS [%d]===\n", i++);
		linked_commands = cur_arg->data;
		j = 0;
		cur_lcmd = linked_commands->tail->next;
		while (cur_lcmd != linked_commands->tail)
		{
			printf("---LINKED COMMANDS [%d]---\n", j++);
			commands = cur_lcmd->data;
			printf("COMMAND: %s\n", commands->syntax->input);
			printf("MEANING: ");
			for (int x = 0; x < (int)ft_strlen(commands->syntax->input); x++)
				printf("%d", commands->syntax->meaning[x]);
			printf("\n");
			if (commands->prev == AND)
				printf("LINKER : AND\n");
			else if (commands->prev == OR)
				printf("LINKER : OR\n");
			else
				printf("LINKER : NONE\n");
			cur_lcmd = cur_lcmd->next;
		}
		cur_arg = cur_arg->next;
	}
	printf("===========END===========\033[0m\n");
}

void	print_deq_of_syntax(t_deq *deq)
{
	t_gnode *cur;
	t_syntax *syntax;

	printf("\033[0;31m===PIPED ARGS===\n");
	cur = deq->tail->next;
	while (cur != deq->tail)
	{
		syntax = cur->data;
		printf("COMMAND: %s\n", syntax->input);
		cur = cur->next;
	}
	printf("\033[0m\n");
}

void	print_deq_of_string(t_deq *deq, char *identifier)
{
	t_gnode *cur;
	char 	*str;
	int		i = 0;

	printf("\033[0;34m---%s---\n", identifier);
	cur = deq->tail->next;
	while (cur != deq->tail)
	{
		str = cur->data;
		printf("[%d]: %s\n", i++, str);
		cur = cur->next;
	}
	printf("\033[0m\n");
}

void	print_argv(char **argv)
{
	printf("\033[0;34m==ARGV==\n");
	for (int i = 0; argv[i]; i++)
		printf("[%d] %s\n", i, argv[i]);
	printf("\033[0m\n");
}

void	print_syntax(t_syntax *s)
{
	printf("\033[0;31m[SYNTAX]\n");
	printf("INPUT  : %s\n", s->input);
	printf("MEANING: ");
	for (int x = 0; x < (int)ft_strlen(s->input); x++)
		printf("%d", s->meaning[x]);
	printf("\n");
	printf("[END]\033[0m\n");
}

void	foo(void)
{
	;
}

void	print_piped_commands(t_deq *piped_commands)
{	
	t_gnode		*cur_cmd;
	t_command	*cmd;
	int		i = 0;

	cur_cmd = piped_commands->tail->next;
	while (cur_cmd != piped_commands->tail)
	{
		printf("\033[0;34m===PIPE[%d]===\n", i++);
		cmd = cur_cmd->data;
		print_argv(cmd->argv);
		print_deq_of_string(cmd->input, "INPUT");
		print_deq_of_string(cmd->output, "OUTPUT");
		cur_cmd = cur_cmd->next;
	}
	printf("\033[0;34m===========END===========\033[0m\n");
}
