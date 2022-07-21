/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:13:17 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/19 14:56:32 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_name(char *name, int n);

void	do_builtin_export(char **argv)
{
	int		i;
	char	*delim;

	i = 1;
	while (argv[i])
	{
		delim = ft_strchr(argv[i], '=');
		if (delim == argv[i])
		{
			printf("minishell: bad assignment\n");
			argv[i][0] = 0;
		}
		else if (delim != 0 && check_name(argv[i], delim - argv[i]) != 0)
			argv[i][0] = 0;
		i++;
	}
	env_commands(PUT_ENV, argv + 1);
}

static int	check_name(char *name, int n)
{
	int	i;

	i = 0;
	if ('0' <= name[0] && name[0] <= '9')
	{
		name[n] = 0;
		printf("export: not an identifier: %s\n", name);
		name[n] = '=';
		return (-1);
	}
	while (i < n)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			name[n] = 0;
			printf("export: not valid in this context: %s\n", name);
			name[n] = '=';
			return (-1);
		}
		i++;
	}
	return (0);
}
