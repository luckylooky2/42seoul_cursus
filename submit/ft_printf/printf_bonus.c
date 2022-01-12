/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:10:41 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/12 11:10:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_bonus.h"

static char	*read_flag(const char *format, t_option *opt)
{
	while (*format == '-' || *format == ' ' || *format == '+'
		|| *format == '#' || *format == '0')
	{
		if (*format == '-')
			opt->f_minus = 1;
		else if (*format == ' ')
			opt->f_space = 1;
		else if (*format == '+')
			opt->f_plus = 1;
		else if (*format == '#')
			opt->f_sharp = 1;
		else if (*format == '0')
			opt->f_zero = 1;
		format++;
	}
	return ((char *)format);
}

static char	*read_width_and_precision(const char *format, t_option *opt)
{
	while ('0' <= *format && *format <= '9')
	{
		opt->width = opt->width * 10 + *format - '0';
		format++;
	}
	if (*format == '.')
	{
		format++;
		opt->dot = 1;
		while ('0' <= *format && *format <= '9')
		{
			opt->prcs = opt->prcs * 10 + *format - '0';
			format++;
		}
	}
	return ((char *)format);
}

static char	*read_type(const char *format, va_list ap, int *ret, t_option *opt)
{
	if (*format == 'c' || *format == 's')
		format = type_cs(format, ap, ret, opt);
	else if (*format == 'p' || *format == '%')
		format = type_p(format, ap, ret, opt);
	else if (*format == 'd' || *format == 'i')
		format = type_int(format, ap, ret, opt);
	else if (*format == 'u')
		format = type_uint(format, ap, ret, opt);
	else if (*format == 'x' || *format == 'X')
		format = type_hex(format, ap, ret, opt);
	if (format == NULL)
		return (NULL);
	return ((char *)format);
}

static int	read_format(const char *format, va_list ap, int *ret, t_option *opt)
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			ft_memset(opt, 0, sizeof(t_option));
			format = read_flag(format, opt);
			format = read_width_and_precision(format, opt);
			format = read_type(format, ap, ret, opt);
		}
		else
			print_stdin((char *)format, ret, 1);
		if (format == NULL)
			return (1);
		format++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			flag;
	int			ret;
	t_option	opt;

	ret = 0;
	va_start(ap, format);
	flag = read_format(format, ap, &ret, &opt);
	va_end(ap);
	if (flag == 1)
		return (-1);
	else
		return (ret);
}

// #include <limits.h>
// #include <stdio.h>
// int main()
// {
// 	// int a = 12334;
// 	// ft_printf("%-1.12s\n%-15.3s\n", "Hello, world!", "12345");
// 	// printf("%-1.12s\n%-15.3s\n", "Hello, world!", "12345");

// 	printf("%d\n", ft_printf(" %#X ", -1));
// 	printf("%d\n", printf(" %#X ", -1));

// // 	ft_printf("%2.12s\n", "12345");
// // 	printf("%2.12s\n", "12345");
// }
