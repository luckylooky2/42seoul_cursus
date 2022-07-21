/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:28:09 by youhan            #+#    #+#             */
/*   Updated: 2022/07/07 20:32:47 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_token_pipe(char **cmd, int **status)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (error_token_check(cmd[i], status[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	error_token_opr(char ***cmd, int ***status)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (error_token_pipe(cmd[i], status[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	error_token(t_cmd cmd)
{
	int	i;

	i = 0;
	while (cmd.p_cmd[i])
	{
		if (error_token_opr(cmd.p_cmd[i], cmd.p_status[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}
