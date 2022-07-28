/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:21:40 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/27 23:52:27 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// heredoc 파이프를 열고 직접 써주는 함수
static int	here_doc(char *str)
{
	char	*input;
	int		here_doc[2];

	if (pipe(here_doc) == -1)
		pnaic("Failed to create pipe.");
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		input = ft_gnl(STDIN_FILENO);
		if (input == NULL)
			break ;
		// limiter과 일치하면 break
		if (!ft_strncmp(str + 3, input, ft_strlen(str + 3)) && \
		input[ft_strlen(input) - 1] == '\n')
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, here_doc[WRITE]);
		free(input);
	}
	close(here_doc[WRITE]); // 사용한 write end 닫아주기
	return (here_doc[READ]); // read end return
}

static void	close_fd(void *n)
{
	close((int)n);
}

int	heredoc_manager(t_heredoc_cmd cmd, char *delimiter)
{
	// heredoc fd만 관리하는 deq?
	static t_deq	*fds = NULL;
	int				id;

	if (fds == NULL)
	{
		fds = ft_deq_new();
		if (fds == NULL)
			panic_memory();
	}
	// fds deq free()
	if (cmd == CLOSE_HEREDOC)
		ft_deq_delete(&fds, close_fd);
	// heredoc 추가
	else if (cmd == PUT_HEREDOC)
	{
		id = here_doc(delimiter);
		if (ft_deq_push_back(fds, (void *)(long)id) == -1)
			panic_memory();
		return (id);
	}
	return (0);
}

// piped_commands : t_command 구조체를 담고 있는 t_deq
static void	do_heredoc(t_deq *piped_commands)
{
	t_gnode		*piped_unit;
	t_gnode		*input_unit;
	t_command	*command;
	char		*input_file;
	int			id;

	piped_unit = piped_commands->tail->next;
	// piped_commands 순회
	while (piped_unit != piped_commands->tail)
	{
		input_unit = command->input->tail->next;
		// piped_commands->input deq 순회
		while (input_unit != command->input->tail)
		{
			input_file = input_unit->data;
			if (input_file[1] == '<')
			{
				// heredoc을 여는 flag : PUT_HEREDOC, id는 fd?
				id = heredoc_manager(PUT_HEREDOC, input_file);
				free(input_file);
				input_unit->data = ft_itoa(id);
			}
			input_unit = input_unit->next;
		}
		piped_unit = piped_unit->next;
	}
}

// 모든 deq을 돌면서 heredoc을 처리하는 함수
void	process_heredoc(t_deq *broken_semicolon)
{
	t_deq		*linked_commands;
	t_gnode		*semicolon_unit;
	t_gnode		*linked_unit;
	t_commands	*commands;

	semicolon_unit = broken_semicolon->tail->next;
	while (semicolon_unit != broken_semicolon->tail)
	{
		linked_commands = semicolon_unit->data;
		linked_unit = linked_commands->tail->next;
		while (linked_unit != linked_commands->tail)
		{
			commands = linked_unit->data;
			do_heredoc(commands->piped_commands);
			linked_unit = linked_unit->next;
		}
		semicolon_unit = semicolon_unit->next;
	}
}