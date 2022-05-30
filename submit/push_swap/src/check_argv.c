/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:40:43 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/30 18:46:04 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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

int	count_argc(char *argv[])
{
	int	cnt;

	cnt = 1;
	while (argv[cnt] != NULL)
		cnt++;
	return (cnt);
}
