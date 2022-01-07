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

void	print_sharp(int *ret, t_option *opt)
{
	if (opt->type == 'x')
		write(1, "0x", 2);
	else if (opt->type == 'X')
		write(1, "0X", 2);
	*ret += 2;
}

void	write_and_plus(char *sg_char, int *ret, int flag)
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
