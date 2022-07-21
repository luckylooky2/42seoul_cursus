/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:58:55 by youhan            #+#    #+#             */
/*   Updated: 2022/07/12 21:38:25 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_str(char *str, char start, int *status)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == start) && status[i] == -1)
			return (i);
		i++;
	}
	return (-1);
}

int	skip_push_str(char fin, t_cmd *cmd, int start)
{
	int	i;

	i = start + 1;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == fin && cmd->status[0][i] == -1)
		{
			cmd->status[0][i] = -3 - start;
			if (fin == '\"')
				cmd->status[0][i] = start;
			cmd->cmd_mod[i] = cmd->cmd[i];
			return (i);
		}
		cmd->cmd_mod[i] = cmd->cmd[i];
		cmd->status[0][i] = -3 - start;
		if (fin == '\"')
			cmd->status[0][i] = start;
		i++;
	}
	return (-1);
}

void	change_str(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if ((cmd->cmd[i] == '\"' || cmd->cmd[i] == '\'')
			&& cmd->status[0][i] == -1)
		{
			cmd->status[0][i] = -3 - i;
			if (cmd->cmd[i] == '\"')
				cmd->status[0][i] = i;
			cmd->cmd_mod[i] = cmd->cmd[i];
			i = skip_push_str(cmd->cmd[i], cmd, i) + 1;
		}
		else
		{
			cmd->cmd_mod[i] = cmd->cmd[i];
			i++;
		}
	}
}

int	count_str(char *str, int *status)
{
	int	i;
	int	len;
	int	diff;

	i = 0;
	diff = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && status[i] == -1)
		{
			if (skip_str(&str[i + 1], str[i], &status[i + 1]) == -1)
				return (-1);
			i += skip_str(&str[i + 1], str[i], &status[i + 1]) + 2;
			diff++;
		}
		else
			i++;
	}
	return (i - (2 * diff));
}

int	del_quotes(t_cmd *cmd)
{
	if (count_str(cmd->cmd, cmd->status[0]) == -1)
		return (-1);
	cmd->cmd_mod = (char *)malloc(sizeof(char) * ft_strlen(cmd->cmd) + 1);
	if (cmd->cmd_mod == NULL)
		exit(-1);
	cmd->cmd_mod[ft_strlen(cmd->cmd)] = '\0';
	change_str(cmd);
	return (1);
}
