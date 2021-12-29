/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 22:27:17 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/27 22:27:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	flag_switch_fuction(int *ret, int (*opt)[9], int len, int i)
{
	if ((*opt)[0] == 0 && (*opt)[4] == 1)
	{
		i = flag_print_plus(ret, opt, i);
		flag_print_space_or_zero(ret, opt, len, i);
		return ;
	}
	i = flag_print_space_or_zero(ret, opt, len, i);
	flag_print_plus(ret, opt, i);
}

int	flag_print_plus(int *ret, int (*opt)[9], int i)
{
	if ((*opt)[2] == 1)
	{
		write(1, "+", 1);
		i++;
		(*ret)++;
	}
	else if ((*opt)[1] == 1)
	{
		write(1, " ", 1);
		i++;
		(*ret)++;
	}
	return (i);
}

int	flag_print_space_or_zero(int *ret, int (*opt)[9], int len, int i)
{
	int	flag;

	flag = 0;
	if (((*opt)[0] != 0 || (*opt)[4] != 1)
		&& (*opt)[8] == 2 && ((*opt)[1] == 1 || (*opt)[2] == 1))
		flag = 1;
	while ((*opt)[5] - len - flag - i > 0)
	{
		if ((*opt)[0] == 0 && (*opt)[4] == 1)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		i++;
		(*ret)++;
	}
	return (i);
}

void	flag_print_string(const char *str, int *ret, int (*opt)[9], int flag)
{
	int	i;
	int	len;
	int	opt_nb;

	i = 0;
	opt_nb = 5;
	len = (int)ft_strlen(str);
	if ((*opt)[0] == 1)
	{
		i = flag_print_plus(ret, opt, i);
		i = print_string(str, ret, opt);
		flag_print_space_or_zero(ret, opt, 0, i);
	}
	else if ((*opt)[0] == 0)
	{
		if (flag == 1)
			opt_nb = 7;
		if ((int)ft_strlen(str) > (*opt)[opt_nb])
			len = (*opt)[opt_nb];
		flag_switch_fuction(ret, opt, len, i);
		print_string(str, ret, opt);
	}
}
