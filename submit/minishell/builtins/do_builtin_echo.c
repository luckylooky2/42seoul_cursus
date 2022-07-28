/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:13:36 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 21:35:25 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_new_line(char **str, int *i)
{
	int	j;
	int	flag;

	flag = 1;
	while (str[*i])
	{
		if (str[*i] == NULL)
			return (flag);
		if (str[*i][0] != '-')
			return (flag);
		j = 1;
		while (str[*i][j])
		{
			if (str[*i][j] != 'n')
				return (flag);
			j++;
		}
		if (j == 1)
			return (flag);
		flag = 0;
		*i += 1;
	}
	return (flag);
}

void	do_builtin_echo(char **argv)
{
	int		i;
	int		j;
	int		new_line;

	i = 1;
	new_line = is_new_line(argv, &i);
	j = i;
	while (argv[i])
	{
		if ((i == j && ft_printf("%s", argv[i]) == -1) || \
		(i != j && ft_printf(" %s", argv[i]) == -1))
		{
			error_errno("echo");
			global_status(SET_STATUS, 1);
			return ;
		}
		i++;
	}
	if (new_line && ft_printf("\n") == -1)
	{
		error_errno("echo");
		global_status(SET_STATUS, 1);
		return ;
	}
	global_status(SET_STATUS, 0);
}
