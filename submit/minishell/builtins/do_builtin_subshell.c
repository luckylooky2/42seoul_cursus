/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_subshell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:13:05 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/20 12:28:45 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_command_subshell(char *arg)
{
	size_t	arg_len;

	arg_len = ft_strlen(arg);
	return (3 <= arg_len && arg[0] == '(' && arg[arg_len - 1] == ')');
}

void	do_builtin_subshell(char **argv)
{
	char	*new_argv[3];	

	new_argv[0] = "./minishell";
	new_argv[1] = argv[0] + 1;
	new_argv[1][ft_strlen(argv[0]) - 2] = 0;
	new_argv[2] = 0;
	if (execve(new_argv[0], new_argv, (char **)env_commands(LIST_ENV, NULL)) \
	== -1)
		error_exit(new_argv[0]);
}
