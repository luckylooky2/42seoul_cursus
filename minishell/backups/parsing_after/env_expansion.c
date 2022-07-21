/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:28:34 by youhan            #+#    #+#             */
/*   Updated: 2022/07/12 21:11:59 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_group_expansion(char *cmd, int *status)
{
	int	i;
	int	group;

	i = 1;
	group = status[0];
	while (cmd[i])
	{
		if (cmd[i] == '$' && status[i] >= -1)
			return (i - 1);
		if (group == status[i])
			i++;
		else
			return (i - 1);
	}
	return (i - 1);
}

int	check_expansion(char *cmd, int *status)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && status[i] >= -1)
		{
			if (check_group_expansion(&(cmd[i]), &(status[i])))
				return (-1);	
		}
		i++;
	}
	return (1);
}

char	*get_path(char *cmd, int size)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		panic(NULL);
	while (i < size)
	{
		tmp[i] = cmd[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
} 

int	count_expansion(char *cmd, int *status)
{
	int		count;
	int		i;
	char	*a;
	char	*tmp[2];

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && status[i] >= -1)
		{
			if (check_group_expansion(&(cmd[i]), &(status[i])) > 0)
			{
				tmp[0] = get_path(&(cmd[i + 1]), check_group_expansion(&(cmd[i]), &(status[i])));
				tmp[1] = NULL;
				a = getenv((tmp)[0]); // 수정
				if (ft_strlen(a) == 1 && a[0] == '?')
				{
					a = ft_itoa(global_status("GET_STAT", 0));
				}
				count += ft_strlen((a));
				i += check_group_expansion(&(cmd[i]), &(status[i]));
				free(tmp[0]);
			}
			else
				count += 1;
		}
		else
			count += 1;
		i++;
	}
	return (count);
}

void	init_str_int(int *str, int fin)
{
	int	i;

	i = 0;
	if (i < fin)
	{
		str[i] = 0;
		i++;
	}
}

void	push_expansion(char *cmd, int *status, char **cmd_m, int **cmd_s)
{
	int		i;
	int		j;
	char	*tmp[2];
	char	*a;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && status[i] >= -1)
		{			
			if (check_group_expansion(&(cmd[i]), &(status[i])) > 0)
			{
				tmp[0] = get_path(&(cmd[i + 1]), check_group_expansion(&(cmd[i]), &(status[i])));
				tmp[1] = NULL;
				a = getenv(tmp[0]); // 수정
				if (ft_strlen(a) == 1 && a[0] == '?')
				{
					a = ft_itoa(global_status("GET_STAT", 0));
				}
				ft_strncpy_char(&((*cmd_m)[j]), a, ft_strlen(a));
				init_str_int(&((*cmd_s)[j]), ft_strlen(a));
				j += ft_strlen(a);
				i += check_group_expansion(&(cmd[i]), &(status[i]));
				// free(a);
				free(tmp[0]);
			}
			else
			{
				(*cmd_m)[j] = cmd[i];
				(*cmd_s)[j] = status[i];
				j++;
			}

		}
		else
		{
			(*cmd_m)[j] = cmd[i];
			(*cmd_s)[j] = status[i];
			j++;
		}
		i++;
	}
}

int	env_expansion(char **cmd, int **status)
{
	int	len;
	char	*cmd_m;
	int		*cmd_s;

	// if (check_expansion(*cmd, *status) == -1)
	// 	return (1);
	len = count_expansion(*cmd, *status);
	cmd_m = (char *)malloc(sizeof(char) * (len + 1));
	cmd_s = (int *)malloc(sizeof(int) * len);
	cmd_m[len] = '\0';
	if (cmd_m == NULL || cmd_s == NULL)
		panic(NULL);
	push_expansion(*cmd, *status, &cmd_m, &cmd_s);
	free(*cmd);
	free(*status);
	*cmd = cmd_m;
	*status = cmd_s;
	return (1);
}

int	pipe_del_expansion(char ***cmd, int	***cmd_status)
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
			env_expansion(&(cmd[i][j]), &(cmd_status[i][j]));
			printf("%s\n\n\n", cmd[i][j]);
			j++;
		}
		i++;
	}
	return (1);
}
