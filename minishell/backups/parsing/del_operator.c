/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:07:00 by youhan            #+#    #+#             */
/*   Updated: 2022/07/07 16:08:23 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delim_bracket(char *cmd, int *status, int **bracket)
{
	int	val;
	int	i;

	i = 0;
	val = 1;
	while (cmd[i] && cmd[i + 1])
	{
		if (bool_conditional(cmd, status, *bracket, i) == 1)
		{
			(*bracket)[i] = val;
			(*bracket)[i + 1] = val;
			i++;
		}
		val++;
		i++;
	}
}

int	split_operator(char *cmd, int *status, char ***opr, int ***opr_s)
{
	int	*bracket;

	if (init_bracket(cmd, &bracket, status) == -1)
		return (-1);
	delim_bracket(cmd, status, &bracket);
	(*opr) = push_operator(cmd, status, opr_s, bracket);
	free(bracket);
	return (1);
}

int	del_operator(t_cmd *cmd)
{
	int	i;

	i = count_char_pointer_2(cmd->mod);
	(cmd->opr_cmd) = (char ***)malloc(sizeof(char **) * (i + 1));
	(cmd->opr_status) = (int ***)malloc(sizeof(int **) * i);
	if (cmd->opr_cmd == NULL || (cmd->opr_status) == NULL)
		return (-1);
	cmd->opr_cmd[i] = NULL;
	i = 0;
	while (cmd->mod[i])
	{
		if (split_operator(cmd->mod[i], cmd->mod_status[i],
				&cmd->opr_cmd[i], &cmd->opr_status[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}
