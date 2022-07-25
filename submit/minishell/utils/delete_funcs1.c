/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_funcs1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 18:54:13 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 17:10:56 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_t_command(void *cmd)
{
	t_command	*command;

	if (cmd == NULL)
		return ;
	command = cmd;
	delete_str_array(command->argv);
	command->argv = NULL;
	delete_t_syntax(command->syntax);
	command->syntax = NULL;
	ft_deq_delete(&command->input, free);
	ft_deq_delete(&command->output, free);
	free(cmd);
}

void	delete_t_commands(void *cmd)
{
	t_commands	*commands;

	if (cmd == NULL)
		return ;
	commands = cmd;
	delete_t_syntax(commands->syntax);
	ft_deq_delete(&commands->piped_commands, delete_t_command);
	free(cmd);
}

void	delete_linked_commands(void *l_cmd)
{
	t_deq	*linked_commands;

	if (l_cmd == NULL)
		return ;
	linked_commands = l_cmd;
	ft_deq_delete(&linked_commands, delete_t_commands);
}

void	delete_t_env(void *arg)
{
	t_env	*env;

	if (arg == NULL)
		return ;
	env = arg;
	free(env->key);
	env->key = NULL;
	free(env->value);
	env->value = NULL;
	free(env);
}

void	delete_t_syntax(void *arg)
{
	t_syntax	*syntax;

	if (arg == NULL)
		return ;
	syntax = arg;
	free(syntax->input);
	syntax->input = NULL;
	free(syntax->meaning);
	syntax->meaning = NULL;
	free(arg);
}
