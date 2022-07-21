/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:31:07 by youhan            #+#    #+#             */
/*   Updated: 2022/07/11 22:59:09 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_bracket(char **cmd, int *status)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (count_bracket(cmd[i], status) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	split_move_space(const char *str, int *status, int i)
{
	while (str[i])
	{
		if (str[i] == ' ' && status[i] == -1)
			i++;
		else
			return (i);
	}
	return (i);
}

void	ft_strncpy_int(int *dest, int *src, unsigned int n)
{
	unsigned int	a;

	a = 0;
	if (n == 0)
		return ;
	while (a < n)
	{
		dest[a] = src[a];
		a++;
	}
}

void	ft_strncpy_char(char *dest, char *src, unsigned int n)
{
	unsigned int	a;

	a = 0;
	if (n == 0)
	{
		dest[a] = '\0';
		return ;
	}
	while (src[a] && a < n)
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
}
