/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:56:24 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/26 23:55:11 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

 /* signal()을 실행시키는 함수 */
t_sig_handler	ft_signal(int signum, t_sig_handler handler)
{
	t_sig_handler	old_action;

	old_action = signal(signum, handler);
	if (old_action == SIG_ERR)
		panic("Signal handler failed to set.");
	return (old_action);
}

void	remove_signal_message(int signum)
{
	ft_printf("\b\b  \b\b"); // SIGQUIT이 안 되었던 이유? 버퍼 관리 때문에
	if (signum == SIGINT)
		ft_printf("\n"); // SIGINT가 되었던 이유? '\n'을 출력해주기 때문에
}

/* 결국에는 signal()을 동작시키기 위한 함수 */
void	sigint_handler(int signum)
{
	t_sig_handler	old_action; // 서브쉘에서 다르게 동작시키기 위해 기본 동작을 기억하는 구조체

	if (signum == SIGINT)
	{
		if (global_status(GET_INTERACTIVE, 0)) // 기본 쉘 동작
		{
			remove_signal_message(signum);
			rl_on_new_line();
			rl_replace_line("", STDOUT_FILENO);
			rl_redisplay();
		}
		else // cat과 같은 동작 : SIGINT를 무시
		{
			old_action = ft_signal(SIGINT, SIG_IGN); // 서브쉘을 위한 old_action return
			ft_signal(SIGINT, old_action);
		}
	}
}

void	sigquit_handler(int signum)
{
	t_sig_handler	old_action; // 서브쉘에서 다르게 동작시키기 위해 기본 동작을 기억하는 구조체

	if (signum == SIGQUIT)
	{
		if (global_status(GET_INTERACTIVE, 0)) // 기본 쉘 동작
			remove_signal_message(signum);
		else // cat과 같은 동작 : SIGQUIT을 무시
		{
			old_action = ft_signal(SIGQUIT, SIG_IGN);
			ft_signal(SIGQUIT, old_action);
		}
	}
}
