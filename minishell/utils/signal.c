/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:56:24 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/19 15:00:02 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	if (signum == SIGINT)
	{
		if (global_status(GET_INTERACTIVE, 0))
		{
			remove_signal_message(signum);
			rl_on_new_line();
			rl_replace_line("", STDOUT_FILENO);
			rl_redisplay();
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
			old_action = ft_signal(SIGQUIT, SIG_IGN);
			ft_signal(SIGQUIT, old_action);
		}
	}
}
