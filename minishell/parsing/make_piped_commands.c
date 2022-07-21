/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_piped_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:14:20 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/19 15:22:30 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_command	*make_command(t_syntax *syntax)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		panic_memory();
	command->input = ft_deq_new();
	command->output = ft_deq_new();
	// make redirection(syntax, command)
	expand_env(syntax, 0);
	expand_asterisk(syntax, 0);
	command->argv = break_space(syntax);
	return (command);
}

t_deq	*make_piped_commands(t_syntax *syntax)
{
	t_deq		*piped_commands;
	t_gnode		*broken_unit;
	t_command	*command;

	piped_commands = break_pipe(syntax);
	broken_unit = piped_commands->tail->next;
	while (broken_unit != piped_commands->tail)
	{
		command = make_command(broken_unit->data);
		delete_t_syntax(broken_unit->data);
		broken_unit->data = command;
		broken_unit = broken_unit->next;
	}
	return (piped_commands);
}
