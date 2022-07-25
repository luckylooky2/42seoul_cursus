/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:59:53 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/22 21:45:14 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_proc(t_state *s, char **env, t_command *cmd, int order)
{
	if (input_redirection(s, cmd->input, order) == -1 || \
	output_redirection(s, cmd->output, order) == -1)
		exit(1);
	if (get_builtin_enum(cmd->argv) != NON_SUPPORTING)
	{
		do_builtin(cmd->argv);
		exit(global_status(GET_STATUS, 0));
	}
	else if (execve(find_cmd_in_path(s, cmd->argv[0]), cmd->argv, env) == -1)
		error_exit(cmd->argv[0]);
}

static void	play_one_cmd(t_state *s, char **env, t_command *cmd, int order)
{
	if (get_builtin_enum(cmd->argv) != NON_SUPPORTING && \
	get_builtin_enum(cmd->argv) != SUBSHELL)
	{
		if (order != 0)
		{
			control_in_and_out(BACKUP_IN);
			control_in_and_out(BACKUP_OUT);
			if (input_redirection(s, cmd->input, 0) == -1 || \
			output_redirection(s, cmd->output, 0) == -1)
			{
				control_in_and_out(RESTORE_IN);
				control_in_and_out(RESTORE_OUT);
				return ;
			}
			do_builtin(cmd->argv);
			control_in_and_out(RESTORE_IN);
			control_in_and_out(RESTORE_OUT);
			s->builtin_flag = 1;
		}
		else
			exit(0);
	}
	else if (order == 0)
		child_proc(s, env, cmd, order);
}

void	play_cmd(t_state *s, char **env, t_deq *commands)
{
	int			order;
	t_command	*cmd;

	order = 0;
	while (order < s->pid_cnt && s->pid[order] != 0)
		order++;
	if (s->pid_cnt == 1)
	{
		cmd = ft_deq_get(commands, 0)->data;
		play_one_cmd(s, env, cmd, order);
	}
	else if (order < s->pid_cnt)
	{
		cmd = ft_deq_get(commands, order)->data;
		child_proc(s, env, cmd, order);
	}
	delete_str_array(env);
}
