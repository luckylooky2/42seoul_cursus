/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:09:46 by youhan            #+#    #+#             */
/*   Updated: 2022/07/07 20:24:30 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bool_conditional_space(char *cmd, int *status, int *bracket, int i)
{
	if (bracket[i] < -1)
		return (-1);
	if (cmd[i] == ' ' && status[i] == -1)
		return (1);
	return (-1);
}

int	bool_conditional_pipe(char *cmd, int *status, int *bracket, int i)
{
	if (bracket[i] < -1)
		return (-1);
	if (cmd[i] == '|' && status[i] == -1)
		return (1);
	return (-1);
}

int	bool_conditional(char *cmd, int *status, int *bracket, int i)
{
	if (bracket[i] < -1)
		return (-1);
	if (cmd[i] == '|' && cmd[i + 1] == '|'
		&& status[i + 1] == -1 && status[i] == -1)
		return (1);
	if (cmd[i] == '&' && cmd[i + 1] == '&'
		&& status[i + 1] == -1 && status[i] == -1)
		return (1);
	return (-1);
}

int	split_move(const char *str, int *status, int i)
{
	while (str[i])
	{
		if (status[i] == 1)
		{
			i--;
			return (i);
		}
		i++;
	}
	return (i);
}
