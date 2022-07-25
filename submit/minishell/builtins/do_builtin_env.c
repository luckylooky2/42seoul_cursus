/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:12:13 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/19 14:56:19 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_builtin_env(char **argv)
{
	char	**result;
	int		i;

	(void)argv;
	result = (char **)env_commands(LIST_ENV, NULL);
	i = 0;
	while (result[i])
	{
		if (printf("%s\n", result[i++]) == -1)
		{
			error_errno("env");
			global_status(SET_STATUS, 1);
			delete_str_array(result);
			return ;
		}
	}
	delete_str_array(result);
	global_status(SET_STATUS, 0);
}
