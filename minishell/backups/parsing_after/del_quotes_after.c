/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:17:21 by youhan            #+#    #+#             */
/*   Updated: 2022/07/12 21:50:07 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	skip_str_after(char *str, int start)
// {
// 	int	i;

// 	i = start + 1;
// 	while (str[i])
// 	{
// 		if (str[i] == str[start])
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// int	skip_push_str_after(char *str, char **cmd_mod, int **cmd_status, int *start)
// {
// 	int	i;
// 	int	j;

// 	j = start[1];
// 	i = start[0] + 1;
// 	printf("asd: %p\n", *cmd_mod);
// 	while (str[i])
// 	{
// 		if (str[i] == str[start[0]])
// 			return (i - 1);
// 		(*cmd_mod)[start[1]] = str[i];
// 		start[1] += 1;
// 		i++;
// 	}
// 	return (-1);
// }


// void	change_str_after(char **cmd, int **status, char **cmd_mod, int **cmd_status)
// {
// 	int	i[2];

// 	i[0] = 0;
// 	i[1] = 0;
// 	while ((*cmd)[i[0]])
// 	{
// 		if ((*cmd)[i[0]] == '\"' || (*cmd)[i[0]] == '\'')
// 			i[0] = skip_push_str_after(*cmd, cmd_mod, cmd_status, i) + 2;
// 		else
// 		{
// 			(*cmd_mod)[i[1]] = (*cmd)[i[0]];
// 			(*cmd_status)[i[1]] = -1;
// 			i[0] += 1;
// 			i[1] += 1;
// 		}
// 		printf("d : %d\n", i[0]);
// 	}
// 	return ;
// }

// int	count_str_after(char *str)
// {
// 	int	i;
// 	int	len;
// 	int	diff;

// 	i = 0;
// 	diff = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 		{
// 			if (skip_str_after(str, i) == -1)
// 				return (-1);
// 			i += skip_str_after(str, i) + 2;
// 			diff++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (i - (2 * diff));
// }

// int	del_quotes_after(char **cmd, int **status)
// {
// 	char	*cmd_mod;
// 	int		*cmd_status;

// 	if (cmd == NULL)
// 		return (-1);
// 	if (*cmd == NULL)
// 		return (-1);
// 	if (count_str_after(*cmd) == -1)
// 		return (-1);
// 	cmd_mod = (char *)malloc(sizeof(char) * count_str_after(*cmd) + 1);
// 	cmd_status = (int *)malloc(sizeof(int) * count_str_after(*cmd));
// 	if (cmd_mod == NULL || cmd_status == NULL)
// 		exit(-1);
// 	cmd_mod[count_str_after(*cmd)] = '\0';
// 	change_str_after(cmd, status, &cmd_mod, &cmd_status);
// 	free(*cmd);
// 	free(*status);
// 	*cmd = cmd_mod;
// 	*status = cmd_status;
// 	return (1);
// }


int	skip_str_after(char *str, char start, int *status)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == start) && (status[i] >= 0 || status[i] <= -3))
			return (i);
		i++;
	}
	return (-1);
}

int	skip_push_str_after(char *str, char **cmd_mod, int **cmd_status, int  *start)
{
	int	i;
	int	j;

	j = *start;
	i = 1;
	while (str[i])
	{
		if (str[i] == str[0])
			return (i - 1);
		(*cmd_mod)[*start] = str[i];
		(*cmd_status)[*start] = j;
		*start += 1;
		i++;
	}
	return (-1);
}


void	change_str_after(char *cmd, int *status, char **cmd_mod, int **cmd_status)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '\"' || cmd[i] == '\'') && (status[i] >= 0 || status[i] <= -3))
		{
			i += skip_push_str_after(&cmd[i], cmd_mod, cmd_status, &j);
			i += 2;
		}
		else
		{
			(*cmd_mod)[j] = cmd[i];
			(*cmd_status)[j] = -2;
			if (status[i] != -2)
				(*cmd_status)[j] = -1;
			i++;
			j++;
		}
	}
}

int	count_str_after(char *str, int *status)
{
	int	i;
	int	len;
	int	diff;

	i = 0;
	diff = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && (status[i] >= 0 || status[i] <= -3))
		{
			if (skip_str_after(&str[i + 1], str[i], &status[i + 1]) == -1)
				return (-1);
			i += skip_str_after(&str[i + 1], str[i], &status[i + 1]) + 2;
			diff++;
		}
		else
			i++;
	}
	return (i - (2 * diff));
}

int	del_quotes_after(char **cmd, int **status)
{
	char	*cmd_mod;
	int		*cmd_status;

	if (count_str_after(*cmd, *status) == -1)
		return (-1);
	cmd_mod = (char *)malloc(sizeof(char) * count_str_after(*cmd, *status) + 1);
	cmd_status = (int *)malloc(sizeof(int) * count_str_after(*cmd, *status));
	if (cmd_mod == NULL || cmd_status == NULL)
		exit(-1);
	cmd_mod[count_str_after(*cmd, *status)] = 0;
	change_str_after(*cmd, *status, &cmd_mod, &cmd_status);
	free(*cmd);
	free(*status);
	*cmd = cmd_mod;
	*status = cmd_status;
	return (1);
}

int	del_afer(char ***cmd, int ***cmd_status)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			printf("%s\n",cmd[i][j]);
			del_quotes_after(&(cmd[i][j]), &(cmd_status[i][j]));
			printf("%s\n\n\n", cmd[i][j]);
			j++;
		}
		i++;
	}
	return (1);
}