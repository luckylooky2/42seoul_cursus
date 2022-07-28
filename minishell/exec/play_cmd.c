/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:07:57 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/29 01:07:17 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_proc(t_state *s, char **env, t_command *cmd, int order)
{
	input_redirection(s, cmd->input, order);
	output_redirection(s, cmd->output, order);
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
	// subshell이면 execve를 해야하기 때문에 
	if (get_builtin_enum(cmd->argv) != NON_SUPPORTING && \
	get_builtin_enum(cmd->argv) != SUBSHELL && get_builtin_enum(cmd->argv) != BLANK)
	{
		if (order != 0)
		{
			control_in_and_out(BACKUP_IN);
			control_in_and_out(BACKUP_OUT);
		}
		else
			exit(0);
	}
	// 
	else if (order == 0)
		child_proc(s, env, cmd, order);
}

void	play_cmd(t_state *s, char **env, t_deq *commands)
{
	int			order;
	t_command	*cmd;

	order = 0;
	// 몇 번째 자식인지?
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