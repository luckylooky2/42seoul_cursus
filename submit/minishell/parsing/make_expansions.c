/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:14:20 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/24 14:08:29 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_deq	*make_expansions(t_deq	*piped_commands)
{
	t_gnode		*broken_unit;
	t_command	*command;

	broken_unit = piped_commands->tail->next;
	while (broken_unit != piped_commands->tail)
	{
		if (broken_unit != piped_commands->tail->next)
			global_status(SET_STATUS, 0);
		command = broken_unit->data;
		expand_env(command->syntax, 0);
		expand_asterisk(command->syntax, 0);
		command->argv = break_space(command->syntax);
		broken_unit = broken_unit->next;
	}
	return (piped_commands);
}
