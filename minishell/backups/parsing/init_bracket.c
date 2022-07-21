/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:25:36 by youhan            #+#    #+#             */
/*   Updated: 2022/07/12 21:02:48 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_int_index(int **status, int start, int fin, int val)
{
	int	i;

	i = start;
	while (i <= fin)
	{
		(*status)[i] = val;
		i++;
	}
}

int	change_status_bracket(char *str, int **path, int *status)
{
	int	i;
	int	start_bracket;
	int	val;

	i = 0;
	val = -2;
	while (str[i])
	{
		if (str[i] == '(' && status[i] == -1)
		{
			start_bracket = i;
			i = find_close_bracket(str, status, i + 1);
			change_int_index(path, start_bracket, i, val);
			val--;
		}
		else if (str[i] == ')' && status[i] == -1)
			return (-1);
		if (str[i] == ';' && status[i] == -1)
			(*path)[i] = 1;
		i++;
	}
	return (1);
}

void	init_status(char *cmd, int **status)
{
	int	i;

	i = 0;
	while (i < ft_strlen(cmd))
	{
		(*status)[i] = 0;
		i++;
	}
}

int	init_bracket(char *cmd, int **path, int *status)
{
	(*path) = (int *)malloc(sizeof(int) * ft_strlen(cmd));
	if ((*path) == NULL)
		return (-1);
	init_status(cmd, path);
	change_status_bracket(cmd, path, status);
	return (1);
}
