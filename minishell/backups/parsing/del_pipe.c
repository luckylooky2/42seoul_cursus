/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:35:00 by youhan            #+#    #+#             */
/*   Updated: 2022/07/05 21:42:57 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_bracket(char *cmd, int *status, int **bracket)
{
	int	val;
	int	i;

	i = 0;
	val = 1;
	while (cmd[i])
	{
		if (bool_conditional_pipe(cmd, status, *bracket, i) == 1)
			(*bracket)[i] = val;
		val++;
		i++;
	}
}

int	split_pipe(t_cmd *cmd, int i, int j)
{
	int	k;
	int	*bracket;

	if (init_bracket(cmd->opr_cmd[i][j], &bracket, cmd->opr_status[i][j]) == -1)
		return (-1);
	pipe_bracket(cmd->opr_cmd[i][j], cmd->opr_status[i][j], &bracket);
	cmd->p_cmd[i][j] = push_pipe(cmd->opr_cmd[i][j],
			cmd->opr_status[i][j], &cmd->p_status[i][j], bracket);
	free(bracket);
	return (1);
}

int	div_pipe_opr(t_cmd *cmd, int i)
{
	int	j;

	j = count_char_pointer_2(cmd->opr_cmd[i]);
	(cmd->p_cmd)[i] = (char ***)malloc(sizeof(char **) * (j + 1));
	(cmd->p_status)[i] = (int ***)malloc(sizeof(int **) * j);
	if (cmd->p_cmd[i] == NULL || cmd->p_status[i] == NULL)
		return (-1);
	cmd->p_cmd[i][j] = NULL;
	j = 0;
	while (cmd->opr_cmd[i][j])
	{
		if (split_pipe(cmd, i, j) == -1)
			return (-1);
		j++;
	}
	return (1);
}

int	del_pipe(t_cmd *cmd)
{
	int	i;

	i = count_char_pointer_3(cmd->opr_cmd);
	cmd->p_cmd = (char ****)malloc(sizeof(char ***) * (i + 1));
	cmd->p_status = (int ****)malloc(sizeof(int ***) * i);
	if (cmd->p_cmd == NULL || cmd->p_status == NULL)
		return (-1);
	cmd->p_cmd[i] = NULL;
	i = 0;
	while (cmd->opr_cmd[i])
	{
		if (div_pipe_opr(cmd, i) == -1)
			return (-1);
		i++;
	}
	return (1);
}
