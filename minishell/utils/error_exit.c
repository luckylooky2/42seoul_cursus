/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:59:12 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/18 18:28:15 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *str, char *flag)
{
	char	*error_msg;

	error_msg = ft_strjoin(str, flag);
	ft_putendl_fd(error_msg, 2);
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
	printf("[ERROR] %s\n", message);
}

void	error_errno(void)
{
	error_handle(strerror(errno));
}

void	panic(char *message)
{
	printf("[ERROR] %s\n", message);
	exit(1);
}

void	panic_memory(void)
{
	panic("Failed to allocate memory.");
}
