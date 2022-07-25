/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:01 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 21:16:34 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_with_status(char *num_str)
{
	int		n;
	char	flag;
	char	*temp;
	char	*message;

	n = atoi_s(num_str, &flag);
	if (flag)
	{
		temp = ft_strjoin(num_str, ": numeric argument required.");
		message = ft_strjoin("exit: ", temp);
		error_handle(message);
		free(message);
		free(temp);
		exit(255);
	}
	else
		exit(n);
}

static void	do_exit(char **argv)
{
	int	cnt;

	cnt = 0;
	while (argv[cnt])
		cnt++;
	if (cnt == 1)
		exit(0);
	else if (cnt == 2)
		exit_with_status(argv[1]);
	if (2 < cnt)
	{
		error_handle("exit: too many arguments.");
		exit(255);
	}
}

void	do_builtin(char **argv)
{
	t_builtin	b_enum;

	b_enum = get_builtin_enum(argv);
	if (b_enum == EXIT)
		do_exit(argv);
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

static int	ft_strcmp(const char *s1, const char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

t_builtin	get_builtin_enum(char **argv)
{
	char	*first_arg;

	first_arg = argv[0];
	if (first_arg == NULL)
		return (BLANK);
	else if (!ft_strcmp("exit", first_arg))
		return (EXIT);
	else if (!ft_strcmp("cd", first_arg))
		return (CD);
	else if (!ft_strcmp("echo", first_arg))
		return (ECHO);
	else if (!ft_strcmp("env", first_arg))
		return (ENV);
	else if (!ft_strcmp("export", first_arg))
		return (EXPORT);
	else if (!ft_strcmp("pwd", first_arg))
		return (PWD);
	else if (!ft_strcmp("unset", first_arg))
		return (UNSET);
	else if (is_command_subshell(first_arg))
		return (SUBSHELL);
	else
		return (NON_SUPPORTING);
}
