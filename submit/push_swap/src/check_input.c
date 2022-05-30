/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:23:32 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/30 18:11:54 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	check_number(char *argv[], int i, int j)
{
	if (!(('0' <= argv[i][j] && argv[i][j] <= '9') || argv[i][j] == '+' ||
	argv[i][j] == '-') || (('0' <= argv[i][j] && argv[i][j] <= '9') &&
	(argv[i][j + 1] == '+' || argv[i][j + 1] == '-')) ||
	((argv[i][j] == '+' || argv[i][j] == '-') &&
	!('0' <= argv[i][j + 1] && argv[i][j + 1] <= '9')))
		return (0);
	return (1);
}

static int	check_zero(char *argv_num, int cnt)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (argv_num[0] == '+' || argv_num[0] == '-' || argv_num[0] == '0')
		i++;
	while (argv_num[i])
	{
		if (argv_num[i] != '0')
			flag = 1;
		if (flag == 1)
			cnt++;
		i++;
	}
	return (cnt);
}

int	check_input(int ac, char *av[])
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		cnt = 0;
		while (av[i][++j])
		{
			if (check_number(av, i, j) == 0)
				return (-1);
		}
		cnt = check_zero(av[i], cnt);
		if (cnt > 11 || ft_atoll(av[i]) < -2147483648LL)
			return (-1);
		if (cnt > 11 || ft_atoll(av[i]) > 2147483647LL)
			return (-1);
	}
	return (0);
}

int	check_blank(char *str)
{
	int	blank;
	int	i;

	blank = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			blank++;
		i++;
	}
	if (i == 0 || i == blank)
		return (1);
	return (0);
}

char	**parse_input(char *argv[])
{
	char	**new_argv;
	char	*str;
	int		cnt;

	new_argv = NULL;
	str = NULL;
	cnt = 1;
	while (argv[cnt])
	{
		str = ft_strjoin(&str, argv[cnt]);
		if (str == NULL)
			return (NULL);
		if (check_blank(argv[cnt]) == 1)
		{
			free(str);
			argv[1] = NULL;
			return (argv);
		}
		cnt++;
	}
	new_argv = ft_split(str, ' ');
	free(str);
	return (new_argv);
}
