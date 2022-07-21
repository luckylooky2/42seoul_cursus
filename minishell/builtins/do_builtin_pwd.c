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

	path = getcwd(NULL, 0);
	if (path == 0)
	{
		printf("pwd: %s\n", strerror(errno));
		return ;
	}
	printf("%s\n", path);
	free(path);
	(void) argv;
}
