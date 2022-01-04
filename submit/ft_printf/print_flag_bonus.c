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

void	flag_switch_fuction(int *ret, int (*opt)[10], int len, int i)
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

int	flag_print_plus(int *ret, int (*opt)[10], int i)
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

int	flag_print_space_or_zero(int *ret, int (*opt)[10], int len, int i)
{
	int	flag;
	int	opt_nb;

	opt_nb = 5;
	flag = 0;
	if (((*opt)[0] != 0 || (*opt)[4] != 1)
		&& (*opt)[8] == 2 && ((*opt)[1] == 1 || (*opt)[2] == 1) && (*opt)[9] != 1)
		flag = 1;
	if ((*opt)[8] == 2 && (*opt)[9] == 1 && (*opt)[0] == 0 && (*opt)[6] == 0)
		flag++;
	if ((*opt)[8] == 2 && (*opt)[6] == 1 || ((*opt)[8] == 4 && (*opt)[6] == 1))
		opt_nb = 7;
	// printf("opt : %d\n", opt_nb);
	// printf("%d\n", (*opt)[opt_nb]);
	// printf("%d\n", len);
	// printf("%d\n", flag);
	// printf("%d\n", i);
	while ((*opt)[opt_nb] - len - flag - i > 0)
	{
		if ((*opt)[0] == 0 && ((*opt)[4] == 1 || (*opt)[6] == 1))
			write(1, "0", 1);
		else
			write(1, " ", 1);
		i++;
		(*ret)++;
	}
	return (i);
}

void	flag_print_string(char *str, int *ret, int (*opt)[10], int flag)
{
	int	i;
	int	len;
	int	opt_nb;

	i = 0;
	opt_nb = 5;
	len = (int)ft_strlen(str);
	if (str[0] == '-' && (*opt)[8] == 2)
		len--;
	if ((*opt)[6] == 1 && len > (*opt)[7])
	{
		// printf("1\n");
		(*opt)[7] = len;
		if (str[0] == '-' && (*opt)[8] == 2)
		{
			write(1, "-", 1);
			(*ret)++;
		}
		print_string(str, ret, opt);
	}
	else if ((*opt)[0] == 1)
	{
		// printf("2\n");
		i = flag_print_plus(ret, opt, i);
		if (str[0] == '-' && (*opt)[8] == 2)
		{
			write(1, "-", 1);
			(*ret)++;
			(*opt)[9] = 1;
		}
		i = print_string(str, ret, opt);
		flag_print_space_or_zero(ret, opt, 0, i);
	}
	else if ((*opt)[0] == 0)
	{
		// printf("3\n");
		// printf("len : %d\n", len);
		if (flag == 1 && (*opt)[6] == 1 || (*opt)[8] == 4)
			opt_nb = 7;
		if (len > (*opt)[opt_nb])
			len = (*opt)[opt_nb];
		if (str[0] == '-' && (*opt)[8] == 2)
		{
			write(1, "-", 1);
			(*ret)++;
			(*opt)[9] = 1;
		}
		// printf("len : %d\n", len);
		// printf("s : %s\n", str);
		flag_switch_fuction(ret, opt, len, i);
		print_string(str, ret, opt);
	}
}
