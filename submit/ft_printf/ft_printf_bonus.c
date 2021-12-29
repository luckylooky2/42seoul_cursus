/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:02:04 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/29 12:25:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*read_flag(const char *format, int (*opt)[9])
{
	while (*format == '-' || *format == ' ' || *format == '+'
		|| *format == '#' || *format == '0')
	{
		if (*format == '-')
			(*opt)[0] = 1;
		else if (*format == ' ')
			(*opt)[1] = 1;
		else if (*format == '+')
			(*opt)[2] = 1;
		else if (*format == '#')
			(*opt)[3] = 1;
		else if (*format == '0')
			(*opt)[4] = 1;
		format++;
	}
	return ((char *)format);
}

static char	*read_width_and_precision(const char *format, int (*opt)[9])
{
	while ('0' <= *format && *format <= '9')
	{
		(*opt)[5] = (*opt)[5] * 10 + *format - '0';
		format++;
	}
	if (*format == '.')
	{
		format++;
		(*opt)[6] = 1;
		while ('0' <= *format && *format <= '9')
		{
			(*opt)[7] = (*opt)[7] * 10 + *format - '0';
			format++;
		}
	}
	return ((char *)format);
}

static char	*read_type(const char *format, va_list ap, int *ret, int (*opt)[9])
{
	if (*format == 'c' || *format == 's')
		format = print_cs(format, ap, ret, opt);
	else if (*format == 'p' || *format == '%')
		format = print_p(format, ap, ret, opt);
	else if (*format == 'd' || *format == 'i')
		format = print_int(format, ap, ret, opt);
	else if (*format == 'u')
		format = print_uint(format, ap, ret, opt);
	else if (*format == 'x' || *format == 'X')
		format = print_hex(format, ap, ret, opt);
	if (format == NULL)
		return (NULL);
	return ((char *)format);
}

static int	read_format(const char *format, va_list ap, int *ret, int (*opt)[9])
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			ft_memset(*opt, 0, sizeof(int) * 9);
			format = read_flag(format, opt);
			format = read_width_and_precision(format, opt);
			format = read_type(format, ap, ret, opt);
		}
		else
		{
			write(1, format, 1);
			(*ret)++;
		}
		if (format == NULL)
			return (1);
		format++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		flag;
	int		ret;
	int		opt[9];

	ret = 0;
	va_start(ap, format);
	flag = read_format(format, ap, &ret, &opt);
	va_end(ap);
	if (flag == 1)
		return (-1);
	else
		return (ret);
}

// int main()
// {
// 	// int a = 12334;
// 	// ft_printf("%-1.12s\n%-15.3s\n", "Hello, world!", "12345");
// 	// printf("%-1.12s\n%-15.3s\n", "Hello, world!", "12345");

// 	ft_printf("%+ 010d\n", 123125);
// 	printf("%+ 010d\n", 123125);

// // 	ft_printf("%2.12s\n", "12345");
// // 	printf("%2.12s\n", "12345");
// }
