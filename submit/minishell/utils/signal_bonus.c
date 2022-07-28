/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:56:24 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:59:16 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

t_sig_handler	ft_signal(int signum, t_sig_handler handler)
{
	t_sig_handler	old_action;

	old_action = signal(signum, handler);
	if (old_action == SIG_ERR)
		panic("Signal handler failed to set.");
	return (old_action);
}

static void	remove_signal_message(int signum)
{
	printf("\b\b  \b\b");
	if (signum == SIGINT)
		printf("\n");
}

void	sigint_handler(int signum)
{
	t_sig_handler	old_action;
	t_int_status	status;

	if (signum == SIGINT)
	{
		status = global_status(GET_INTERACTIVE, 0);
		if (status == INTERACTIVE)
		{
			remove_signal_message(signum);
			rl_on_new_line();
			rl_replace_line("", STDOUT_FILENO);
			rl_redisplay();
		}
		else if (status == HEREDOC)
		{
			close(STDIN_FILENO);
			remove_signal_message(signum);
			global_status(SET_INTERACTIVE, INTERACTIVE);
		}
		else
		{
			old_action = ft_signal(SIGINT, SIG_IGN);
			ft_signal(SIGINT, old_action);
		}
	}
}

void	sigquit_handler(int signum)
{
	t_sig_handler	old_action;

	if (signum == SIGQUIT)
	{
		if (global_status(GET_INTERACTIVE, 0))
			remove_signal_message(signum);
		else
		{
			global_status(SET_INTERACTIVE, 1);
			old_action = ft_signal(SIGQUIT, SIG_IGN);
			ft_signal(SIGQUIT, old_action);
		}
	}
}
