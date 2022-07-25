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
	char	*command_with_colon;
	char	*error_msg;

	command_with_colon = ft_strjoin(command, ": ");
	if (errno != ENOENT)
		error_msg = ft_strjoin(command_with_colon, strerror(errno));
	else
		error_msg = ft_strjoin(command_with_colon, "command not found.");
	error_handle(error_msg);
	free(error_msg);
	free(command_with_colon);
	if (errno == ENOENT)
		exit(127);
	else
		exit(1);
}

void	error_handle(char *message)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: ", message);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free(error_msg);
}

void	error_errno(char *prefix)
{
	char	*prefix_with_colon;
	char	*error_msg;

	prefix_with_colon = ft_strjoin(prefix, ": ");
	error_msg = ft_strjoin(prefix_with_colon, strerror(errno));
	error_handle(error_msg);
	free(error_msg);
	free(prefix_with_colon);
}

void	panic(char *message)
{
	error_handle(message);
	exit(1);
}

void	panic_memory(void)
{
	panic("Failed to allocate memory.");
}
