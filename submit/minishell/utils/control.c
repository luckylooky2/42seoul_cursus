/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:48:26 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 20:59:18 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	control_in_and_out(t_control c)
{
	static int	backup[2] = {-1, -1};

	if (c == BACKUP_IN)
		backup[READ] = dup(STDIN_FILENO);
	else if (c == BACKUP_OUT)
		backup[WRITE] = dup(STDIN_FILENO);
	else if (c == RESTORE_IN)
	{
		close(STDIN_FILENO);
		dup2(backup[READ], STDIN_FILENO);
		backup[READ] = -1;
	}
	else if (c == RESTORE_OUT)
	{
		close(STDOUT_FILENO);
		dup2(backup[WRITE], STDOUT_FILENO);
		backup[WRITE] = -1;
	}
}
