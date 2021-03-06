/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:06:35 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:57:14 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static void	wait_child(t_state *s)
{
	int		stat;
	int		i;

	i = 0;
	while (i < s->pid_cnt)
		waitpid(s->pid[i++], &(stat), 0);
	if (!s->builtin_flag)
		global_status(SET_STATUS, WEXITSTATUS(stat));
}

void	do_exec(t_deq *commands)
{
	t_state	s;
	char	**path;

	ft_memset(&s, 0, sizeof(s));
	s.pid_cnt = commands->size;
	s.pipe_cnt = s.pid_cnt - 1;
	path = ft_split("PATH", ' ');
	s.path = path_check(env_commands(GET_ENV, path));
	delete_str_array(path);
	make_proc_pipe(&s);
	play_cmd(&s, (char **)env_commands(LIST_ENV, NULL), commands);
	wait_child(&s);
	delete_t_state(&s);
}
