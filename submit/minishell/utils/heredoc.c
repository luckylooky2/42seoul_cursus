/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:57:56 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 21:11:44 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	here_doc(char *str)
{
	char	*input;
	int		here_doc[2];

	if (pipe(here_doc) == -1)
		panic("Failed to create pipe.");
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		input = ft_gnl(STDIN_FILENO);
		if (input == NULL)
			break ;
		if (!ft_strncmp(str + 3, input, ft_strlen(str + 3)) && \
		input[ft_strlen(input) - 1] == '\n')
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, here_doc[WRITE]);
		free(input);
	}
	close(here_doc[WRITE]);
	return (here_doc[READ]);
}

static void	close_fd(void *n)
{
	close((int)(long)n);
}

int	heredoc_manager(t_heredoc_cmd cmd, char *delimiter)
{
	static t_deq	*fds = NULL;
	int				id;

	if (fds == NULL)
	{
		fds = ft_deq_new();
		if (fds == NULL)
			panic_memory();
	}
	if (cmd == CLOSE_HEREDOC)
		ft_deq_delete(&fds, close_fd);
	else if (cmd == PUT_HEREDOC)
	{
		id = here_doc(delimiter);
		if (ft_deq_push_back(fds, (void *)(long)id) == -1)
			panic_memory();
		return (id);
	}
	return (0);
}

static void	do_heredoc(t_deq *piped_commands)
{
	t_gnode		*piped_unit;
	t_gnode		*input_unit;
	t_command	*command;
	char		*input_file;
	int			id;

	piped_unit = piped_commands->tail->next;
	while (piped_unit != piped_commands->tail)
	{
		command = piped_unit->data;
		input_unit = command->input->tail->next;
		while (input_unit != command->input->tail)
		{
			input_file = input_unit->data;
			if (input_file[1] == '<')
			{
				id = heredoc_manager(PUT_HEREDOC, input_file);
				free(input_file);
				input_unit->data = ft_itoa(id);
			}
			input_unit = input_unit->next;
		}
		piped_unit = piped_unit->next;
	}
}

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
