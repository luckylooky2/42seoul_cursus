/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:01 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/17 20:38:21 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_builtin(char **argv)
{
	t_builtin	b_enum;

	b_enum = get_builtin_enum(argv);
	if (b_enum == EXIT)
		exit(0);
	else if (b_enum == CD)
		do_builtin_cd(argv);
	else if (b_enum == ECHO)
		do_builtin_echo(argv);
	else if (b_enum == ENV)
		do_builtin_env(argv);
	else if (b_enum == EXPORT)
		do_builtin_export(argv);
	else if (b_enum == PWD)
		do_builtin_pwd(argv);
	else if (b_enum == UNSET)
		do_builtin_unset(argv);
	else if (b_enum == SUBSHELL)
		do_builtin_subshell(argv);
}

t_builtin	get_builtin_enum(char **argv)
{
	char	*first_arg;

	first_arg = argv[0];
	if (first_arg == NULL)
		return (BLANK);
	else if (ft_strncmp("exit", first_arg, 5) == 0)
		return (EXIT);
	else if (ft_strncmp("cd", first_arg, 3) == 0)
		return (CD);
	else if (ft_strncmp("echo", first_arg, 4) == 0)
		return (ECHO);
	else if (ft_strncmp("env", first_arg, 4) == 0)
		return (ENV);
	else if (ft_strncmp("export", first_arg, 7) == 0)
		return (EXPORT);
	else if (ft_strncmp("pwd", first_arg, 4) == 0)
		return (PWD);
	else if (ft_strncmp("unset", first_arg, 6) == 0)
		return (UNSET);
	else if (is_command_subshell(first_arg))
		return (SUBSHELL);
	else
		return (NON_SUPPORTING);
}
