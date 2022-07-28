/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:13:30 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 14:39:55 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_builtin_cd(char **argv)
{
	char	*prefix;

	if (chdir(argv[1]) == -1)
	{
		if (argv[1] == NULL)
			prefix = ft_strdup("cd");
		else
			prefix = ft_strjoin("cd: ", argv[1]);
		if (prefix == NULL)
			panic_memory();
		error_errno(prefix);
		free(prefix);
		global_status(SET_STATUS, 1);
	}
	else
		global_status(SET_STATUS, 0);
}
