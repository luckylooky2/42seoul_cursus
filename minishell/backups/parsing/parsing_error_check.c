/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:29:28 by youhan            #+#    #+#             */
/*   Updated: 2022/07/12 19:38:32 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	move_space(char *cmd, int *status, int i)
{
	while (cmd[i])
	{
		if (!(cmd[i] == ' ' && status[i] == -1))
			return (i);
		i++;
	}
	return (i);
}

int	error_token_close_bracket(char *cmd, int *status)
{
	int	i;
	int	*bracket;

	i = 0;
	if (init_bracket(cmd, &bracket, status) == -1)
		return (-1);
	i = move_space(cmd, status, i);
	while (cmd[i])
	{
		if (bracket[i] > -2)
			break ;
		i++;
	}
	while (cmd[i])
	{
		if (!(cmd[i] == ' ' && status[i] == -1))
		{
			free(bracket);
			return (-1);
		}
		i++;
	}
	free(bracket);
	return (1);
}

int	error_token_bracket(char *cmd, int *status)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i] == '(' && status[i] == -1)
			flag = 1;
		i++;
	}
	if (flag == 0)
		return (1);
	if (error_token_close_bracket(cmd, status) == -1)
		return (-1);
	if (error_token_brackets(cmd, status) == -1)
		return (-1);
	if (error_token_empty_bracket(cmd, status) == -1)
		return (-1);
	return (1);
}

int	error_token_all_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (1);
		i++;
	}
	return (-1);
}

int	error_token_check(char *cmd, int *status)
{
	int	i;

	i = 0;
	if (ft_strlen(cmd) == 0)
		return (-1);
	if (error_token_all_space(cmd) == -1)
		return (-1);
	if (error_token_bracket(cmd, status) == -1)
		return (-1);
	return (1);
}
