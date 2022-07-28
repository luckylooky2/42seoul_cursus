/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 01:14:16 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/26 19:21:46 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_subshell_error(t_syntax *s)
{
	t_syntax	*s_t;
	char		**argv;
	int			i;

	argv = break_space_const(s);
	i = -1;
	while (argv[++i] && argv[i + 1])
	{
		s_t = syntax_from_input(argv[i + 1], ft_strdup(argv[i + 1]));
		if (s_t == NULL)
			panic_memory();
		if (is_command_subshell(argv[i]))
			parsing_error(s_t, NULL, 0);
		else if (is_command_subshell(argv[i + 1]))
			parsing_error(s_t, NULL, 1);
		else
		{
			delete_t_syntax(s_t);
			continue ;
		}
		delete_t_syntax(s_t);
		global_status(SET_P_ERROR, PRINTED);
		break ;
	}
	delete_str_array(argv);
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
		if (command->input == NULL || command->output == NULL)
			panic_memory();
		command->syntax = syntax;
		remove_redirection(syntax, command);
		check_subshell_error(syntax);
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
			make_command(commands->piped_commands);
			linked_unit = linked_unit->next;
		}
		semicolon_unit = semicolon_unit->next;
	}
}
