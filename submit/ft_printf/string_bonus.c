/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_write_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:46:07 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/07 13:46:09 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_string(char *str, int *ret, t_option *opt)
{
	int	i;

	i = 0;
	if (opt->dot && opt->type == 's' && opt->prcs == 0)
		return (i);
	else if (opt->dot && (opt->type == 'd' || opt->type == 's'))
	{
		if (str[i] == '-' && opt->type == 'd')
			str++;
		while (i < opt->prcs && str[i] != '\0')
			print_stdin(&str[i++], ret, 1);
	}
	else if (opt->type != 'c')
	{
		while (str[i] != '\0')
		{
			if (!(str[i] == '-' && opt->type == 'd'))
				print_stdin(&str[i], ret, 1);
			i++;
		}
	}
	else
		print_stdin(&str[i++], ret, 1);
	return (i);
}

void	print_string_with_option(char *str, int *ret, t_option *opt, int flag)
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
			print_stdin("-", ret, 1);
		print_string(str, ret, opt);
	}
	else if (opt->f_minus)
	{
		i = print_sign(ret, opt, i);
		if (str[0] == '-' && opt->type == 'd')
		{
			print_stdin("-", ret, 1);
			opt->neg = 1;
		}
		i = print_string(str, ret, opt);
		print_padding(ret, opt, 0, i);
	}
	else if (opt->f_minus == 0)
	{
		if ((flag == 1 && opt->dot) || opt->type == 'u')
			sw = opt->prcs;
		if (len > sw && opt->type != 'u' && opt->type != 'x' && opt->type != 'X')
			len = sw;
		if (str[0] == '-' && opt->type == 'd')
		{
			print_stdin("-", ret, 1);
			opt->neg = 1;
		}
		switch_fuction(ret, opt, len, i);
		print_string(str, ret, opt);
	}
}

void	switch_fuction(int *ret, t_option *opt, int len, int i)
{
	if (opt->f_minus == 0 && opt->f_zero)
	{
		i = print_sign(ret, opt, i);
		print_padding(ret, opt, len, i);
	}
	else
	{
		i = print_padding(ret, opt, len, i);
		print_sign(ret, opt, i);
	}
}