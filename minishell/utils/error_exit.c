/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:59:12 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/20 20:08:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *str, char *flag)
{
	char	*error_msg;

	error_msg = ft_strjoin(str, flag);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	if (!ft_strncmp("command not found: ", str, 20))
		exit(127);
	else if (!ft_strncmp("permission denied: ", str, 20))
		exit(1);
	else
		exit(1);
}

void	error_handle(char *message)
{
	write(STDERR_FILENO, "[ERROR] ", 8);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	error_errno(void)
{
	error_handle(strerror(errno));
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
