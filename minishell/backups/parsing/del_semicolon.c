/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_semicolon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:28:35 by youhan            #+#    #+#             */
/*   Updated: 2022/07/07 20:07:50 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_split_mini_while(t_cmd *cmd, int count)
{
	int	i;
	int	path;
	int	save_i;

	i = 0;
	path = 0;
	while (path < count)
	{
		save_i = i;
		i = split_move(cmd->cmd_mod, cmd->status[1], i);
		cmd->mod[path] = (char *)malloc(sizeof(char) * (i - save_i + 2));
		cmd->mod_status[path] = (int *)malloc(sizeof(int) * (i - save_i + 1));
		if (cmd->mod[path] == NULL || cmd->mod_status[path] == NULL)
			return (-1);
		ft_strncpy_char(cmd->mod[path], &cmd->cmd_mod[save_i], i - save_i + 1);
		ft_strncpy_int(cmd->mod_status[path], &cmd->status[0][save_i],
			i - save_i + 1);
		cmd->mod[path][i - save_i + 1] = '\0';
		i += 2;
		path++;
	}
	return (1);
}

int	ft_count_split(const char *str, int *status)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (status[i] == 1)
			count++;
		i++;
	}
	i--;
	while (str[i])
	{
		if (str[i] != ' ')
			break ;
		i--;
	}
	if (status[i] != 1)
		count++;
	return (count);
}

int	ft_split_mini(t_cmd *cmd)
{
	int		path;

	path = ft_count_split(cmd->cmd_mod, cmd->status[1]);
	cmd->mod_status = (int **)malloc(sizeof(int *) * path);
	cmd->mod = (char **)malloc(sizeof(char *) * (path + 1));
	if (cmd->mod == NULL || cmd->mod_status == NULL)
		return (-1);
	cmd->mod[path] = NULL;
	if (ft_split_mini_while(cmd, path) == -1)
		return (-1);
	return (1);
}

int	del_semicolon(t_cmd *cmd)
{
	if (ft_split_mini(cmd) == -1)
		return (-1);
	return (1);
}
