/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_linker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 19:12:00 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 17:23:06 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_delimiter	get_linker_type(char *linker)
{
	if (!ft_strncmp("&&", linker, 2))
		return (AND_AND);
	else
		return (OR_OR);
}

static t_deq	*break_specific_linker(t_syntax *s, char *linker)
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
		if (s->meaning[i] == 1 && ft_strncmp(linker, s->input + i, 2) == 0)
		{
			if (ft_deq_push_back(broken_unit, \
			slice_syntax(s, last, i - last, get_linker_type(linker))) == -1)
				panic_memory();
			last = i++ + 2;
		}
		i++;
	}
	if (ft_deq_push_back(broken_unit, \
	slice_syntax(s, last, i - last, get_linker_type(linker))) == -1)
		panic_memory();
	return (cleanup_deque(broken_unit, delete_t_syntax));
}

static void	link_commands(t_deq *linked_commands, t_deq *broken_and)
{
	int			start;
	t_commands	*commands;

	start = 1;
	while (!ft_deq_is_empty(broken_and))
	{
		commands = ft_calloc(1, sizeof(t_commands));
		if (commands == NULL)
			panic_memory();
		if (start)
		{
			if (linked_commands->size == 0)
				commands->prev = NONE;
			else
				commands->prev = OR;
			start = 0;
		}
		else
			commands->prev = AND;
		commands->syntax = ft_deq_pop_front(broken_and);
		if (ft_deq_push_back(linked_commands, commands) == -1)
			panic_memory();
	}
	ft_deq_delete(&broken_and, delete_t_syntax);
}

static void	break_linker_each(t_syntax *s, t_deq *linked_commands)
{
	t_deq		*broken_or;
	t_gnode		*or_unit;
	t_syntax	*syntax;

	broken_or = break_specific_linker(s, "||");
	or_unit = broken_or->tail->next;
	while (or_unit != broken_or->tail)
	{
		syntax = or_unit->data;
		link_commands(linked_commands, break_specific_linker(syntax, "&&"));
		or_unit = or_unit->next;
	}
	ft_deq_delete(&broken_or, delete_t_syntax);
}

void	break_linker(t_deq *broken_semicolon)
{
	t_deq	*linked_commands;
	t_gnode	*semicolon_unit;

	semicolon_unit = broken_semicolon->tail->next;
	while (semicolon_unit != broken_semicolon->tail)
	{
		linked_commands = ft_deq_new();
		if (linked_commands == NULL)
			panic_memory();
		break_linker_each(semicolon_unit->data, linked_commands);
		delete_t_syntax(semicolon_unit->data);
		semicolon_unit->data = linked_commands;
		semicolon_unit = semicolon_unit->next;
	}
}
