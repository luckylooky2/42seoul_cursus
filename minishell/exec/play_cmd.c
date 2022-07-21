/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:59:53 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/20 20:41:39 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	input_redirection(t_state *s, int pid_num)
{
	if (0 < pid_num)
	{
		if (dup2(s->pipes[pid_num - 1][READ], STDIN_FILENO) == -1)
			panic(strerror(errno));
	}
}

static void	output_redirection(t_state *s, int pid_num)
{
	if (pid_num < s->pipe_cnt)
	{
		if (dup2(s->pipes[pid_num][WRITE], STDOUT_FILENO) == -1)
			panic(strerror(errno));
	}
}

static void	child_proc(t_state *s, char **env, char **cmd, int pid_num)
{
	if (s->pid_cnt != 1)
	{
		input_redirection(s, pid_num);
		output_redirection(s, pid_num);
	}
	if (get_builtin_enum(cmd) != NON_SUPPORTING)
	{
		do_builtin(cmd);
		exit(0);
	}
	else if (execve(find_cmd_in_path(s, cmd[0]), cmd, env) == -1)
		error_exit("command not found: ", cmd[0]);
}

static void	play_one_cmd(t_state *s, char **env, t_command *cmd, int order)
{
	if (get_builtin_enum(cmd->argv) != NON_SUPPORTING && \
	get_builtin_enum(cmd->argv) != SUBSHELL)
	{
		if (order != 0)
		{
			do_builtin(cmd->argv);
			s->builtin_flag = 1;
		}
		else
			exit(0);
	}
	else if (order == 0)
		child_proc(s, env, cmd->argv, order);
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
		child_proc(s, env, cmd->argv, order);
	}
	delete_str_array(env);
}
