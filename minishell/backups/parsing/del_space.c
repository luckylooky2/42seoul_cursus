/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:59:40 by youhan            #+#    #+#             */
/*   Updated: 2022/07/07 20:08:45 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	space_bracket(char *cmd, int *status, int **bracket)
{
	int	val;
	int	i;

	i = 0;
	val = 1;
	while (cmd[i])
	{
		if (bool_conditional_space(cmd, status, *bracket, i) == 1)
			(*bracket)[i] = val;
		val++;
		i++;
	}
}

int	split_space(t_cmd *cmd, int i, int j, int k)
{
	int	*bracket;

	if (init_bracket(cmd->p_cmd[i][j][k], &bracket,
			cmd->p_status[i][j][k]) == -1)
		return (-1);
	space_bracket(cmd->p_cmd[i][j][k], cmd->p_status[i][j][k], &bracket);
	cmd->s_cmd[i][j][k] = push_space(cmd->p_cmd[i][j][k],
			cmd->p_status[i][j][k], &cmd->s_status[i][j][k], bracket);
	free(bracket);
	return (1);
}

int	space_opr(t_cmd *cmd, int i, int j)
{
	int	k;

	k = count_char_pointer_2(cmd->p_cmd[i][j]);
	cmd->s_cmd[i][j] = (char ***)malloc(sizeof(char **) * (k + 1));
	cmd->s_status[i][j] = (int ***)malloc(sizeof(int **) * k);
	if (cmd->s_cmd[i][j] == NULL || cmd->s_status[i][j] == NULL)
		return (-1);
	cmd->s_cmd[i][j][k] = NULL;
	k = 0;
	while (cmd->p_cmd[i][j][k])
	{
		split_space(cmd, i, j, k);
		k++;
	}
	return (1);
}

int	space_pipe(t_cmd *cmd, int i)
{
	int	j;

	j = count_char_pointer_3(cmd->p_cmd[i]);
	cmd->s_cmd[i] = (char ****)malloc(sizeof(char ***) * (j + 1));
	cmd->s_status[i] = (int ****)malloc(sizeof(int ***) * j);
	if (cmd->s_cmd[i] == NULL || cmd->s_status[i] == NULL)
		return (-1);
	cmd->s_cmd[i][j] = NULL;
	j = 0;
	while (cmd->p_cmd[i][j])
	{
		space_opr(cmd, i, j);
		j++;
	}
	return (-1);
}

int	del_space(t_cmd *cmd)
{
	int	i;

	i = count_char_pointer_4(cmd->p_cmd);
	cmd->s_cmd = (char *****)malloc(sizeof(char ****) * (i + 1));
	cmd->s_status = (int *****)malloc(sizeof(int ****) * i);
	if (cmd->s_cmd == NULL || cmd->s_status == NULL)
		return (-1);
	cmd->s_cmd[i] = NULL;
	i = 0;
	while (cmd->p_cmd[i])
	{
		space_pipe(cmd, i);
		i++;
	}
	return (1);
}
