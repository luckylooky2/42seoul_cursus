/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_backslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:06:50 by youhan            #+#    #+#             */
/*   Updated: 2022/07/12 21:46:04 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_backslash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
		{
			i++;
			if (cmd[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (1);
}

int	skip_gruop(char *str, char start)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == start)
			return (i + 1);
		i++;
	}
	return (-1);
}

int	del_backslash(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (check_backslash(cmd->cmd) == -1)
		return (-1);
	cmd->status[0] = (int *)malloc(sizeof(int) * ft_strlen(cmd->cmd));
	if (cmd->status[0] == NULL)
		panic(NULL);
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '\\' && cmd->cmd[i + 1] != '\0')
		{
			cmd->status[0][i] = -2;
			cmd->status[0][i + 1] = -2;
			i++;
		}
		else if (cmd->cmd[i] == '\"' || cmd->cmd[i] == '\'')
		{
			if (skip_gruop(&(cmd->cmd[i + 1]), cmd->cmd[i]) < 0)
				return (-1);
			i += skip_gruop(&(cmd->cmd[i + 1]), cmd->cmd[i]);
		}
		else
			cmd->status[0][i] = -1;
		i++;
	}
	return (1);
}
