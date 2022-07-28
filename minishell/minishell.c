/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:46:29 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 14:56:38 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_deq	*parse_args(char *input)
{
	t_syntax	*syntax;
	t_deq		*broken_semicolon;

	// input 배열과 각 char의 meaning 배열을 가지고 있는 구조체를 생성
	syntax = syntax_from_input(input, make_meaning(input));
	if (syntax == NULL)
		return (NULL);
	// semicolon으로 나누기
	broken_semicolon = break_semicolon(syntax);
	// and, or로 나누기
	break_linker(broken_semicolon);
	// pipe로 나누기
	break_pipe(broken_semicolon);
	delete_t_syntax(syntax);
	// 모든 deq을 완성한 후에 에러가 있으면 free()
	if (global_status(GET_P_ERROR, 0) == PRINTED)
	{
		ft_deq_delete(&broken_semicolon, delete_linked_commands);
		return (NULL);
	}
	process_heredoc(broken_semicolon);
	return (broken_semicolon);
}

static void	do_command(t_deq *linked_commands)
{
	t_gnode		*cur;
	t_commands	*commands;
	int			exit_status;

	cur = linked_commands->tail->next;
	// linked_commands deq 순회
	while (cur != linked_commands->tail)
	{
		commands = cur->data;
		// linker를 기준으로 linker의 종류와 어떻게 종료되었는지를 보고 판단
		// 첫 노드이거나, AND이면서 앞 노드가 성공, OR이면서 앞 노드가 실패시 do_exec() 진행
		exit_status = global_status(GET_STATUS, 0);
		if ((commands->prev == AND && exit_status == 0) || \
		(commands->prev == OR && exit_status != 0) || commands->prev == NONE)
			do_exec(make_expansions(commands->piped_commands));
		cur = cur->next;
	}
}

static void	do_commands(t_deq *broken_semicolon)
{
	t_gnode	*semicolon_unit;

	semicolon_unit = broken_semicolon->tail->next;
	// broken_semicolon deq 순회
	while (semicolon_unit != broken_semicolon->tail)
	{
		do_command(semicolon_unit->data);
		semicolon_unit = semicolon_unit->next;
	}
	// 가장 상위 deq free()
	ft_deq_delete(&broken_semicolon, delete_linked_commands);
}

static int	routine(char *input)
{
	t_deq	*parsed_args;
	char	free_flag;

	global_status(SET_P_ERROR, 0); // parsing error가 없는 상태로 설정
	free_flag = 0;
	if (input == NULL)
	{
		input = readline("\033[0,$ "); // 색이 바뀌는 것을 강제로 흰색으로 지정
		if (input == NULL) // NULL 가드
			return (0);
		free_flag = 1;
		add_history(input);
	}
	// INTERACTIVE : 쉘 기본 동작(1), 실행 단계(0)
	global_status(SET_INTERACTIVE, 0);
	// 모든 파싱이 이루어지는 함수 => t_deq으로 return
	parsed_args = parse_args(input);
	// 실행 단계
	if (parsed_args != NULL)
		do_commands(parsed_args);
	if (free_flag) // readline을 통해 입력한 경우만 free()
		free(input);
	global_status(SET_INTERACTIVE, 1); // INTERACTIVE를 쉘 기본동작(1)으로 변경
	return (1); 
}

int	main(int argc, char **argv, char **envp)
{
	// signal이 입력되었을 때, 다른 동작으로 바꾸기 위한 함수
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	// 환경 변수 초기화 : 현재 환경 변수로 env_list를 초기화
	env_commands(PUT_ENV, envp);
	// argument가 존재하는 경우 (subshell, bash -c)
	if (argc != 1)
	{
		routine(argv[1]); // 첫 번째 argument가 명령어이므로 나머지 argument는 무시
		env_commands(CLOSE_ENV, NULL); // 환경 변수 env_list free()
		exit(global_status(GET_STATUS, 0)); // 프로세스 종료
	}
	printf("hello, world\n");
	return (0);	
}

/*
-- minishell을 하면서 배운 점 --
1. 자료구조 : deq
2. 함수 모듈화 : env_commands(PUT, GET, LIST)
*/