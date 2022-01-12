/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_option_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:11:11 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/12 11:11:17 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_bonus.h"

int	print_sign(int *ret, t_option *opt, int i)
{
	if (opt->f_plus && opt->neg == 0 && opt->type != 's')
	{
		print_stdin("+", ret, 1);
		i++;
	}
	else if (opt->f_space && opt->neg == 0 && opt->type != 's')
	{
		print_stdin(" ", ret, 1);
		i++;
	}
	return (i);
}

int	print_padding(int *ret, t_option *opt, int len, int i)
{
	int	flag;
	int	tot;

	tot = opt->width;
	flag = 0;
	if ((opt->f_minus || opt->f_zero == 0)
		&& opt->type == 'd' && (opt->f_space || opt->f_plus) && opt->neg == 0)
		flag = 1;
	if (opt->type == 'd' && opt->neg && opt->f_minus == 0 && opt->dot == 0)
		flag++;
	if ((opt->type == 'd' || opt->type == 'u'
			|| opt->type == 'x' || opt->type == 'X') && opt->dot)
		tot = opt->prcs;
	while (tot - len - flag - i > 0)
	{
		if (opt->f_minus == 0 && (opt->f_zero || opt->dot))
			print_stdin("0", ret, 1);
		else
			print_stdin(" ", ret, 1);
		i++;
	}
	return (i);
}

void	print_base(int *ret, t_option *opt)
{
	if (opt->type == 'x')
		write(1, "0x", 2);
	else if (opt->type == 'X')
		write(1, "0X", 2);
	*ret += 2;
}

void	print_stdin(char *sg_char, int *ret, int flag)
{
	if (flag == 1)
	{
		write(1, sg_char, 1);
		(*ret)++;
	}
	else if (flag == 0)
	{
		write(1, "(null)", 6);
		*ret += 6;
	}
}
