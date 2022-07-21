/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_result1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:38:04 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/19 20:23:30 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_parser_error_in_subshell(t_syntax *s)
{
	int		i;
	int		j;
	char	*subshell_input;
	t_deq	*parsed_args_in_subshell;

	i = 0;
	while (s->input[i])
	{
		if (s->input[i] == '(' && s->meaning[i] == 1)
		{
			j = i + 1;
			while (s->input[j] != ')' || s->meaning[j] != 1)
				j++;
			subshell_input = ft_substr(s->input, i + 1, j - i - 1);
			if (subshell_input == NULL)
				panic_memory();
			parsed_args_in_subshell = parse_args(subshell_input);
			if (parsed_args_in_subshell == NULL)
				return (1);
			ft_deq_delete(&parsed_args_in_subshell, delete_linked_commands);
			i = j;
		}
		i++;
	}
	return (0);
}

static int	slice_error(void)
{
	int	error;

	error = global_status(GET_P_ERROR, 0);
	if (error == SEMICOLON)
		error_handle("parse error near `;;'");
	else if (error == AND_AND)
		error_handle("parse error near `&&'");
	else if (error == OR_OR)
		error_handle("parse error near `||'");
	else if (error == PIPE)
		error_handle("parse error near `|'");
	else
		return (0);
	return (1);
}

static int	error_on_(t_deq *linked_commands)
{
	t_deq		*piped_commands;
	t_gnode		*linked_unit;
	t_commands	*commands;

	linked_unit = linked_commands->tail->next;
	while (linked_unit != linked_commands->tail)
	{
		commands = linked_unit->data;
		piped_commands = break_pipe(commands->syntax);
		ft_deq_delete(&piped_commands, delete_t_syntax);
		if (parsing_error_on_syntax(commands->syntax) || \
		check_parser_error_in_subshell(commands->syntax) || slice_error())
			return (1);
		linked_unit = linked_unit->next;
	}
	return (0);
}

int	error_on(t_deq *broken_semicolon)
{
	t_deq		*linked_commands;
	t_gnode		*semicolon_unit;

	if (slice_error())
		return (1);
	semicolon_unit = broken_semicolon->tail->next;
	while (semicolon_unit != broken_semicolon->tail)
	{
		linked_commands = semicolon_unit->data;
		if (error_on_(linked_commands))
			return (1);
		semicolon_unit = semicolon_unit->next;
	}
	return (0);
}
