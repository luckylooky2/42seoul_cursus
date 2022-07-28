/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_status_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:46:38 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:59:08 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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
	else if (cmd == SET_STATUS)
		last_exit_status = value;
	else if (cmd == SET_INTERACTIVE)
		interactive = value;
	else if (cmd == SET_P_ERROR)
		parsing_error = value;
	return (0);
}
