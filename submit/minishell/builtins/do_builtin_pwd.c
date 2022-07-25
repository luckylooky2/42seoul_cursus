/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:13:23 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/06 17:38:18 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_builtin_pwd(char **argv)
{
	char	*path;

	(void) argv;
	path = getcwd(NULL, 0);
	if (path == 0)
	{
		error_errno("pwd");
		global_status(SET_STATUS, 1);
		return ;
	}
	printf("%s\n", path);
	free(path);
	global_status(SET_STATUS, 0);
}
