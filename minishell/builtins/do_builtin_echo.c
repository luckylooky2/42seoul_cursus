/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:13:36 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/06 17:38:04 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_no_nl_opt(char *str);

void	do_builtin_echo(char **argv)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 0;
	while (*(++argv))
	{
		if (i == 1)
		{
			new_line = !is_no_nl_opt(*argv);
			if (new_line)
				printf("%s", *argv);
		}
		else if (i == 2 && !new_line)
			printf("%s", *argv);
		else
			printf(" %s", *argv);
		i++;
	}
	if (new_line)
		printf("\n");
}

static int	is_no_nl_opt(char *str)
{
	if (str[0] != '-')
		return (0);
	while (*(++str))
	{
		if (*str != 'n')
			return (0);
	}
	return (1);
}
