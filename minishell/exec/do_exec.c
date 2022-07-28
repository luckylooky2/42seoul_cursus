/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:57:09 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 16:47:17 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_child(t_state *s)
{
	int	stat;
	int	i;

	i = 0;
	// 순서대로 자식이 끝나기를 기다림
	while (i < s->pid_cnt)
		wait_pid(s->pid[i++], &stat, 0);
	// exit status 설정
	if (!s->builtin_flag)
		global_status(SET_STATUS, WEXITSTATUS(stat));
}

// 파싱이 끝난 commands deq(linker 단위)을 실행하는 단계
void	do_exec(t_deq *commands)
{
	t_state	s;
	char	**path;

	ft_memset(&s, 0, sizeof(s)); // t_state 초기화
	// piped_commands deq의 size
	s.pid_cnt = commands->size;
	// 자식 프로세스 - 1
	s.pipe_cnt = s.pid_cnt - 1;
	path = ft_split("PATH", ' ');
	// path로 검색한 환경 변수를 '/'와 함께 연결
	s.path = path_check(env_commands(GET_ENV, path));
	delete_str_array(path); // 다 쓴 변수 삭제
	make_proc_pipe(&s);
	// 현재 환경변수를 가지고 들어감
	play_cmd(&s, (char **)env_commands(LIST_ENV, NULL), commands);
	wait_child(&s);
	delete_t_state(&s);
}