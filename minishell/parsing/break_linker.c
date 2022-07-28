/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_linker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:06:43 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/27 19:18:41 by chanhyle         ###   ########.fr       */
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
		if (s->meaning == 1 && ft_strncmp(linker, s->input + i, 2) == 0)
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

// linked_commands에 각각의 node를 push하는 함수
static void	link_commands(t_deq *linked_commands, t_deq *broken_and)
{
	int			start;
	t_commands	*commands;

	start = 1;
	// deq을 순회
	while (!ft_deq_is_empty(broken_and))
	{
		commands = (t_commands *)ft_calloc(sizeof(t_commands), 1);
		if (commands == NULL)
			panic_memory();
		// 이전 linker 할당
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
		// deq에서 pop
		commands->syntax = ft_deq_pop_front(broken_and);
		// linked_commands에 push
		if (ft_deq_push_back(linked_commands, commands) == -1)
			panic_memory();
	}
	//deq을 free()
	ft_deq_delete(&broken_and, delete_t_syntax);
}

static void	break_linker_each(t_syntax *s, t_deq *linked_commands)
{
	t_deq		*broken_or;
	t_gnode		*or_unit;
	t_syntax	*syntax;

	// ||로 먼저 나눔, broken_or deq을 생성
	broken_or = break_specific_linker(s, "||");
	or_unit = broken_or->tail->next;
	// broken_or을 순회(아직 연결하지 않은 상태)
	while (or_unit != broken_or->tail)
	{
		syntax = or_unit->data;
		// break_specific_linker의 return : deq(아직 연결하지 않은 상태)
		// linked_commands에 차곡차곡 push
		link_commands(linked_commands, break_specific_linker(syntax, "&&"));
		or_unit = or_unit->next;
	}
	ft_deq_delete(&broken_or, delete_t_syntax);
}

// semicolon으로 나눈 deq을 linker로 나누는 함수
void	break_linker(t_deq *broken_semicolon)
{
	// linker로 나눈 deq
	t_deq	*linked_commands;
	t_gnode	*semicolon_unit;

	semicolon_unit = broken_semicolon->tail->next;
	// broken_semicolon deq을 순회
	while (semicolon_unit != broken_semicolon->tail)
	{
		linked_commands = ft_deq_new();
		if (linked_commands == NULL)
			panic_memory();
		// 하나의 node를 deq으로 바꿈
		break_linker_each(semicolon_unit->data, linked_commands);
		// 나누기 전 broken_semicolon deq 노드 free()
		delete_t_syntax(semicolon_unit);
		// 새로 만든 나눠진 deq을 연결
		semicolon_unit->data = linked_commands;
		semicolon_unit = semicolon_unit->next;
	}
}