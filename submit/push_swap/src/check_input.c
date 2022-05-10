/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:23:32 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/08 15:53:34 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	check_input(int ac, char *av[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (!(('0' <= av[i][j] && av[i][j] <= '9') || av[i][j] == '+' ||
				av[i][j] == '-') || (('0' <= av[i][j] && av[i][j] <= '9') &&
				(av[i][j + 1] == '+' || av[i][j + 1] == '-')) ||
				((av[i][j] == '+' || av[i][j] == '-') &&
				!('0' <= av[i][j + 1] && av[i][j + 1] <= '9')))
				return (-1);
		}
		if (av[i][0] == '-' && (j > 11 || ft_atoll(av[i]) < -2147483648LL))
			return (-1);
		if (av[i][0] == '+' && (j > 11 || ft_atoll(av[i]) > 2147483647LL))
			return (-1);
		if ((av[i][0] != '-' && av[i][0] != '+') &&
		(j > 10 || ft_atoll(av[i]) > 2147483647LL))
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

int	count_argc(char *argv[])
{
	int	cnt;

	cnt = 1;
	while (argv[cnt] != NULL)
		cnt++;
	return (cnt);
}