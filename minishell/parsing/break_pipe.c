/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:25:48 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 15:14:15 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 괄호 안에 에러가 있는지 확인하는 함수
static int	check_parse_error_in_subshell(t_syntax *s)
{
	int		i;
	int		j;
	char	*subshell_input;
	t_deq	*parsed_args_in_subshell;

	i = 0;
	while (s->input[i])
	{
		if (s->input[i] == '(' && s->meaning == 1)
		{
			j = i + 1;
			while (s->input[j] != ')' || s->meaning[j] != 1)
				j++;
			subshell_input = s->input + i + 1; // 괄호 다음을 가리키는 포인터
			subshell_input[j - (i + 1)] = 0; // 괄호 끝 '\0'
			parsed_args_in_subshell = parse_args(subshell_input); // 재귀 호출
			subshell_input[j - (i + 1)] = ')'; // 괄호 끝 복구
			if (parsed_args_in_subshell == NULL) // 에러가 있다면 , error_on_parsing에서 free() 후 NULL
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
		error_handle("syntax error near unexpected token `;;'");
	else if (error == AND_AND)
		error_handle("syntax error near unexpected token `&&'");
	else if (error == OR_OR)
		error_handle("syntax error near unexpected token `||'");
	else if (error == PIPE)
		error_handle("syntax error near unexpected token `|'");
	else
		return (0);
	return (1);
}

// 인자로 들어갈 t_command 구조체를 만드는 함수
// linker deq->data(t_commands)->piped_commands(t_deq)
static void	make_command(t_deq	*piped_commands)
{
	t_gnode		*broken_unit;
	t_syntax	*syntax;
	t_command	*command;

	broken_unit = piped_commands->tail->next;
	// piped_commands를 순회
	while (broken_unit != piped_commands->tail)
	{
		syntax = broken_unit->data;
		// 하나하나의 pipe 당 t_commamd 구조체 생성
		command = (t_command *)ft_calloc(sizeof(t_command), 1);
		if (command == NULL)
			panic_memory();
		// input, output redirection도 deq으로 관리
		command->input = ft_deq_new();
		command->output = ft_deq_new();
		command->syntax = syntax;
		// redirection을 지우고 command 구조체에 담는 함수
		remove_redirection(syntax, command);
		// no free()?
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

// broken_semicolon : semicolon deq 안에 linker deq
// linker deq 안에 각각의 data를 pipe 단위로 piped_commands deq을 생성하는 함수
void	break_pipe(t_deq *broken_semicolon)
{
	t_deq		*linked_commands;
	t_gnode		*semicolon_unit;
	t_gnode		*linked_unit;
	t_commands	*commands;

	semicolon_unit = broken_semicolon->tail->next;
	// semicolon deq을 순회
	while (semicolon_unit != broken_semicolon->tail)
	{
		linked_commands = semicolon_unit->data;
		linked_unit = linked_commands->tail->next;
		// linked deq을 순회
		while (linked_unit = linked_commands->tail->next)
		{
			commands = linked_unit->data;
			// deq->data : t_commands->syntax를 바탕으로 t_commands->t_deq을 생성
			commands->piped_commands = break_each_pipe(commands->syntax);
			if (global_status(GET_P_ERROR, 0) != PRINTED && ( \
			// 아래 함수는 빼먹음
			parsing_error_on_syntax(commands->syntax) || \
			check_parse_error_in_subshell(commands->syntax)))
				global_status(SET_P_ERROR, PRINTED);
			make_command(commands->piped_commands);
			linked_unit = linked_unit->next;
		}
		if (slice_error())
			global_status(SET_P_ERROR, PRINTED);
	}
}