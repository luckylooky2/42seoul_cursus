/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:47:10 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/27 14:50:32 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 전역 변수를 관리하는 함수 (getter, setter)
int	global_status(t_global_cmd cmd, int value)
{
	static int	last_exit_status = 0;
	static int	interactive = 1;
	static int	parsing_error = 0;

	if (cmd == GET_STATUS)
		return (last_exit_status);
	else if (cmd == GET_INTERACTIVE)
		return (interactive);
	else if (cmd == GET_P_ERROR)
		return (parsing_error);
	else if (cmd == GET_INTERACTIVE)
		return (interactive);
	else if (cmd == SET_STATUS)
		last_exit_status = value;
	else if (cmd == SET_INTERACTIVE)
		interactive = value;
	else if (cmd == SET_P_ERROR)
		parsing_error = value;
	return (0);
}