/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 00:03:22 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 14:56:37 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// piped_commands deq을 수정한 deq을 반환
t_deq	*make_expansions(t_deq *piped_commands)
{
	t_gnode		*broken_unit;
	t_command	*command;

	broken_unit = piped_commands->tail->next;
	while (broken_unit != piped_commands->tail)
	{
		command = broken_unit->data;
		// 환경 변수 expansion
		expand_env(command->syntax, 0);
		// asterisk expansion
		expand_asterisk(command->syntax, 0);
		// (char **)argv 만드는 과정
		command->argv = break_space(command->syntax);
		// exit status 0으로 초기화
		global_status(SET_STATUS, 0);
		broken_unit = broken_unit->next;
	}
	return (piped_commands);
}