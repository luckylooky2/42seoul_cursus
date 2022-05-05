/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:23:32 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 16:16:37 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_input(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(('0' <= argv[i][j] && argv[i][j] <= '9') ||
				argv[i][j] == '+' || argv[i][j] == '-') ||
				((argv[i][j] == '+' || argv[i][j] == '-') &&
				!('0' <= argv[i][j + 1] && argv[i][j + 1] <= '9')))
				return (-1);
			j++;
		}
		if (argv[i][0] == '-' && (j > 11 ||
			ft_atoll(argv[i]) < -2147483648LL))
			return (-1);
		else if (argv[i][0] != '-' && (j > 10 ||
			ft_atoll(argv[i]) > 2147483647LL))
			return (-1);
	}
	return (0);
}

int	check_repeat(int argc, char *argv[])
{
	int	i;
	int	j;
	int	crt;

	i = 0;
	while (++i < argc)
	{
		j = i + 1;
		crt = ft_atoll(argv[i]);
		while (j < argc)
		{
			if (crt == ft_atoll(argv[j]))
				return (-1);
			j++;
		}
	}
	return (0);
}

char	**parse_input(char *argv[])
{
	char	*str;
	int		cnt;

	cnt = 1;
	str = NULL;
	while (argv[cnt])
	{
		str = ft_strjoin(&str, argv[cnt]);
		cnt++;
	}
	argv = ft_split(str, ' ');
	return (argv);
}

int	count_argc(char *argv[])
{
	int	cnt;

	cnt = 1;
	while (argv[cnt] != NULL)
		cnt++;
	return (cnt);
}
