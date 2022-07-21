/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:01:35 by youhan            #+#    #+#             */
/*   Updated: 2022/07/07 20:27:46 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_pipe_space(char *cmd, int *status, int i, int *bracket)
{
	while (cmd[i])
	{
		if (bracket[i] > 0)
			return (i - 1);
		i++;
	}
	return (i);
}

int	skip_count_space(char *cmd, int *bracket, int *status, int i)
{
	while (cmd[i])
	{
		if (!(cmd[i] == ' ' && status[i] == -1))
			return (i);
		i++;
	}
	return (i);
}

int	count_space(char *cmd, int *bracket, int *status)
{
	int	i;
	int	count;
	int	before;

	count = 0;
	before = 0;
	i = skip_count_space(cmd, bracket, status, 0);
	while (cmd[i])
	{
		if (bracket[i] == 0)
		{
			if (before == 0)
				count++;
			before = 1;
		}
		else
			before = 0;
		i++;
	}
	return (count);
}

char	**push_space(char *cmd, int *status, int ***p_status, int *bracket)
{
	int		i;
	int		save_i;
	int		path;
	char	**result;

	i = count_space(cmd, bracket, status);
	*p_status = (int **)malloc(sizeof(int **) * i);
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (*p_status == NULL || result == NULL)
		panic(NULL);
	result[i] = NULL;
	init_split(&i, &path);
	while (++path < count_space(cmd, bracket, status))
	{
		save_i = skip_count_space(cmd, bracket, status, i);
		i = skip_pipe_space(cmd, status, save_i, bracket);
		result[path] = (char *)malloc(sizeof(char) * (i - save_i + 2));
		(*p_status)[path] = (int *)malloc(sizeof(int) * (i - save_i + 1));
		if (result[path] == NULL || (*p_status)[path] == NULL)
			panic(NULL);
		ft_strncpy_char(result[path], &cmd[save_i], i - save_i + 1);
		ft_strncpy_int((*p_status)[path], &status[save_i], i - save_i + 1);
		i += 1;
	}
	return (result);
}
