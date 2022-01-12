/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:41:26 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/12 12:41:30 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"   

static int	read_format(const char *format, va_list ap, int *ret)
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (*(format + 1) == 'c' || *(format + 1) == 's')
				format = type_char_or_str(format, ap, ret);
			else if (*(format + 1) == 'p' || *(format + 1) == '%')
				format = type_address_or_percent(format, ap, ret);
			else if (*(format + 1) == 'd' || *(format + 1) == 'i')
				format = type_signed_int(format, ap, ret);
			else if (*(format + 1) == 'u')
				format = type_unsigned_int(format, ap, ret);
			else if (*(format + 1) == 'x' || *(format + 1) == 'X')
				format = type_hex(format, ap, ret);
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

	ret = 0;
	va_start(ap, format);
	flag = read_format(format, ap, &ret);
	va_end(ap);
	if (flag == 1)
		return (-1);
	else
		return (ret);
}
