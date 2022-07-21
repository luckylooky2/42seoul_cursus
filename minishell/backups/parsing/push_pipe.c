/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:36:42 by youhan            #+#    #+#             */
/*   Updated: 2022/07/07 20:26:52 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_operator_pipe(char *cmd, int *status, int start, int *bracket)
{
	while (cmd[start])
	{
		if (bool_conditional_pipe(cmd, status, bracket, start) == 1)
			return (start - 1);
		start++;
	}
	return (start);
}

int	count_pipe(char *cmd, int *bracket)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (cmd[i])
	{
		if (bracket[i] > 0 && bracket[i] > 0)
			count++;
		i++;
	}
	return (count);
}

char	**push_pipe(char *cmd, int *status, int ***p_status, int *bracket)
{
	int		i;
	int		save_i;
	int		path;
	char	**result;

	i = count_pipe(cmd, bracket);
	*p_status = (int **)malloc(sizeof(int **) * i);
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (*p_status == NULL || result == NULL)
		panic(NULL);
	result[i] = NULL;
	init_split(&i, &path);
	while (++path < count_pipe(cmd, bracket))
	{
		save_i = i;
		i = skip_operator_pipe(cmd, status, i, bracket);
		result[path] = (char *)malloc(sizeof(char) * (i - save_i + 2));
		(*p_status)[path] = (int *)malloc(sizeof(int) * (i - save_i + 1));
		if (result[path] == NULL || (*p_status)[path] == NULL)
			panic(NULL);
		ft_strncpy_char(result[path], &cmd[save_i], i - save_i + 1);
		ft_strncpy_int((*p_status)[path], &status[save_i], i - save_i + 1);
		i += 2;
	}
	return (result);
}
