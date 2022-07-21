/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:06:35 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/20 20:42:01 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
#ifdef DEBUG_MODE
	print_piped_commands(commands);
#endif
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
	ft_deq_delete(&commands, delete_t_command);
}
