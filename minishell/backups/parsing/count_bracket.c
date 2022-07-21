/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:18:48 by youhan            #+#    #+#             */
/*   Updated: 2022/07/06 18:42:30 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_close_bracket(char *cmd, int *status, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == '(' && status[i] == -1)
		{
			i = find_close_bracket(cmd, status, i + 1);
			if (i == -1)
				return (-1);
		}
		else if (cmd[i] == ')' && status[i] == -1)
			return (i);
		i++;
	}
	return (-1);
}

int	count_bracket(char *cmd, int *status)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '(' && status[i] == -1)
		{
			i = find_close_bracket(cmd, status, i + 1);
			if (i == -1)
				return (-1);
		}
		else if (cmd[i] == ')' && status[i] == -1)
			return (-1);
		i++;
	}
	return (1);
}
