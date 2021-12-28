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

int	flag_print_space(int *ret, int (*opt)[9], int len, int i)
{
	while ((*opt)[5] - len - i > 0)
	{
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
	if ((*opt)[0] == 1)
	{
		i = print_string(str, ret, opt);
		flag_print_space(ret, opt, 0, i);
	}
	else if ((*opt)[0] == 0)
	{
		if (flag == 0)
			opt_nb = 5;
		else if (flag == 1)
			opt_nb = 7;
		if ((int)ft_strlen(str) > (*opt)[opt_nb])
			len = (*opt)[opt_nb];
		else
			len = (int)ft_strlen(str);
		flag_print_space(ret, opt, len, i);
		print_string(str, ret, opt);
	}
}
