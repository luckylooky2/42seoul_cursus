/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:48:26 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/26 20:35:33 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	dup_with_error_handle(int fd)
{
	int	dup_fd;

	dup_fd = dup(fd);
	if (dup_fd == -1)
		panic("redirection failed.");
	return (dup_fd);
}

static void	dup2_with_error_handle(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		panic("redirection failed.");
}

void	control_in_and_out(t_control c)
{
	static int	backup[2] = {-1, -1};
	static int	need_restore = 0;

	if (c == BACKUP_STDIO)
	{
		backup[READ] = dup_with_error_handle(STDIN_FILENO);
		backup[WRITE] = dup_with_error_handle(STDOUT_FILENO);
		need_restore = 1;
	}
	else if (c == RESTORE_STDIO && need_restore)
	{
		dup2_with_error_handle(backup[READ], STDIN_FILENO);
		dup2_with_error_handle(backup[WRITE], STDOUT_FILENO);
		close(backup[READ]);
		close(backup[WRITE]);
		backup[READ] = -1;
		backup[WRITE] = -1;
		need_restore = 0;
	}
}
