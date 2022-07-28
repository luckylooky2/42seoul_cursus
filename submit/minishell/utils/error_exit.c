/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:59:12 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/22 14:39:30 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *command)
{
	char	*error_msg;

	if (errno == ENOENT)
		error_msg = make_message(command, ": ", "command not found.");
	else
		error_msg = make_message(command, ": ", strerror(errno));
	error_handle(error_msg);
	free(error_msg);
	if (errno == ENOENT)
		exit(127);
	else
		exit(1);
}

void	error_handle(char *message)
{
	char	*error_msg;

	error_msg = make_message("minishell: ", message, "\n");
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(error_msg);
}

void	error_errno(char *prefix)
{
	char	*error_msg;

	error_msg = make_message(prefix, ": ", strerror(errno));
	error_handle(error_msg);
	free(error_msg);
}

void	panic(char *message)
{
	error_handle(message);
	exit(1);
}

void	panic_memory(void)
{
	write(STDERR_FILENO, "minishell: Failed to allocate memory.\n", 39);
	exit(1);
}
