/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_check_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:11:52 by youhan            #+#    #+#             */
/*   Updated: 2022/07/12 19:39:00 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_token_brackets(char *cmd, int *status)
{
	int	i;
	int	before;
	int	*bracket;

	if (init_bracket(cmd, &bracket, status) == -1)
	{
		free(bracket);
		return (-1);
	}
	before = 0;
	i = move_space(cmd, status, 0);
	while (cmd[i])
	{
		if (bracket[i] <= -2 && (before == bracket[i] || before == 0))
		{
			before = bracket[i];
		}
		else
		{
			free(bracket);
			return (-1);
		}
		i++;
	}
	free(bracket);
	return (1);
}

int	error_token_empty_bracket(char *cmd, int *status)
{
	int	i;
	int	before;
	int	*bracket;

	if (init_bracket(cmd, &bracket, status) == -1)
	{
		free(bracket);
		return (-1);
	}
	i = move_space(cmd, status, 0) + 1;
	before = bracket[i];
	while (before == bracket[i])
	{
		if (cmd[i] != ')' && cmd[i] != ' ' && status[i] != 1)
		{
			free(bracket);
			return (1);
		}
		i++;
	}
	free(bracket);
	return (-1);
}