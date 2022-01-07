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

void	flag_switch_fuction(int *ret, t_option *opt, int len, int i)
{
	if (opt->f_minus == 0 && opt->f_zero)
	{
		i = flag_print_plus(ret, opt, i);
		flag_print_space_or_zero(ret, opt, len, i);
	}
	else
	{
		i = flag_print_space_or_zero(ret, opt, len, i);
		flag_print_plus(ret, opt, i);
	}
}

int	flag_print_plus(int *ret, t_option *opt, int i)
{
	if (opt->f_plus && opt->neg == 0 && opt->type != 's')
	{
		write_and_plus("+", ret, 1);
		i++;
	}
	else if (opt->f_space && opt->neg == 0 && opt->type != 's')
	{
		write_and_plus(" ", ret, 1);
		i++;
	}
	return (i);
}

int	flag_print_space_or_zero(int *ret, t_option *opt, int len, int i)
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
			write_and_plus("0", ret, 1);
		else
			write_and_plus(" ", ret, 1);
		i++;
	}
	return (i);
}

void	flag_print_string(char *str, int *ret, t_option *opt, int flag)
{
	int	i;
	int	len;
	int	sw;

	i = 0;
	sw = opt->width;
	len = (int)ft_strlen(str);
	if (str[0] == '-' && opt->type == 'd')
		len--;
	if (opt->type != 's' && opt->dot && len > opt->prcs)
	{
		opt->prcs = len;
		if (str[0] == '-' && opt->type == 'd')
			write_and_plus("-", ret, 1);
		ft_print_string(str, ret, opt);
	}
	else if (opt->f_minus)
	{
		i = flag_print_plus(ret, opt, i);
		if (str[0] == '-' && opt->type == 'd')
		{
			write_and_plus("-", ret, 1);
			opt->neg = 1;
		}
		i = ft_print_string(str, ret, opt);
		flag_print_space_or_zero(ret, opt, 0, i);
	}
	else if (opt->f_minus == 0)
	{
		if ((flag == 1 && opt->dot) || opt->type == 'u')
			sw = opt->prcs;
		if (len > sw && opt->type != 'u' && opt->type != 'x' && opt->type != 'X')
			len = sw;
		if (str[0] == '-' && opt->type == 'd')
		{
			write_and_plus("-", ret, 1);
			opt->neg = 1;
		}
		flag_switch_fuction(ret, opt, len, i);
		ft_print_string(str, ret, opt);
	}
}
