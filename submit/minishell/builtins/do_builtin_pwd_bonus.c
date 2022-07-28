/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_pwd_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:13:23 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:56:43 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	do_builtin_pwd(char **argv)
{
	char	*path;

	(void) argv;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		error_errno("pwd");
		global_status(SET_STATUS, 1);
		return ;
	}
	ft_printf("%s\n", path);
	free(path);
	global_status(SET_STATUS, 0);
}
