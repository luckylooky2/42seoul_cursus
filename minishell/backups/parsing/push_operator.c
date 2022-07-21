/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:09:41 by youhan            #+#    #+#             */
/*   Updated: 2022/07/07 20:27:14 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_operator(char *cmd, int *status, int start, int *bracket)
{
	while (cmd[start])
	{
		if (bool_conditional(cmd, status, bracket, start) == 1)
			return (start - 1);
		start++;
	}
	return (start);
}

int	count_oprator(char *cmd, int *bracket)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (cmd[i] && cmd[i + 1])
	{
		if (bracket[i] == bracket[i + 1] && bracket[i] > 0)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

char	**push_operator(char *cmd, int *status, int ***opr_s, int *bracket)
{
	int		i;
	int		save_i;
	int		path;
	char	**result;

	i = count_oprator(cmd, bracket);
	*opr_s = (int **)malloc(sizeof(int **) * i);
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (*opr_s == NULL || result == NULL)
		panic(NULL);
	result[i] = NULL;
	init_split(&i, &path);
	while (++path < count_oprator(cmd, bracket))
	{
		save_i = i;
		i = skip_operator(cmd, status, i, bracket);
		result[path] = (char *)malloc(sizeof(char) * (i - save_i + 2));
		(*opr_s)[path] = (int *)malloc(sizeof(int) * (i - save_i + 1));
		if (result[path] == NULL || (*opr_s)[path] == NULL)
			panic(NULL);
		ft_strncpy_char(result[path], &cmd[save_i], i - save_i + 1);
		ft_strncpy_int((*opr_s)[path], &status[save_i], i - save_i + 1);
		i += 3;
	}
	return (result);
}
