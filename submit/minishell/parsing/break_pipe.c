/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 01:14:16 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/24 17:27:16 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	slice_error(void)
{
	int	error;

	error = global_status(GET_P_ERROR, 0);
	if (error == SEMICOLON)
		parsing_error(NULL, ";;", 0);
	else if (error == AND_AND)
		parsing_error(NULL, "&&", 0);
	else if (error == OR_OR)
		parsing_error(NULL, "||", 0);
	else if (error == PIPE)
		parsing_error(NULL, "|", 0);
	else
		return (0);
	return (1);
}

static void	make_command(t_deq *piped_commands)
{
	t_gnode		*broken_unit;
	t_syntax	*syntax;
	t_command	*command;

	broken_unit = piped_commands->tail->next;
	while (broken_unit != piped_commands->tail)
	{
		syntax = broken_unit->data;
		command = ft_calloc(1, sizeof(t_command));
		if (command == NULL)
			panic_memory();
		command->input = ft_deq_new();
		command->output = ft_deq_new();
		command->syntax = syntax;
		remove_redirection(syntax, command);
		broken_unit->data = command;
		broken_unit = broken_unit->next;
	}
}

static t_deq	*break_each_pipe(t_syntax *s)
{
	t_deq	*broken_unit;
	int		last;
	int		i;

	broken_unit = ft_deq_new();
	if (broken_unit == NULL)
		panic_memory();
	last = 0;
	i = 0;
	while (s->input[i])
	{
		if (s->meaning[i] == 1 && s->input[i] == '|')
		{
			if (ft_deq_push_back(broken_unit, \
			slice_syntax(s, last, i - last, PIPE)) == -1)
				panic_memory();
			last = i + 1;
		}
		i++;
	}
	if (ft_deq_push_back(broken_unit, \
	slice_syntax(s, last, i - last, PIPE)) == -1)
		panic_memory();
	return (cleanup_deque(broken_unit, delete_t_syntax));
}

void	break_pipe(t_deq *broken_semicolon)
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
			commands->piped_commands = break_each_pipe(commands->syntax);
			if (global_status(GET_P_ERROR, 0) != PRINTED && slice_error())
				global_status(SET_P_ERROR, PRINTED);
			make_command(commands->piped_commands);
			linked_unit = linked_unit->next;
		}
		semicolon_unit = semicolon_unit->next;
	}
	if (slice_error())
		global_status(SET_P_ERROR, PRINTED);
}
