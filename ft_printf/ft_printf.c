/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:48:19 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/21 12:06:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static char	*char_or_str(const char *format, va_list ap, int *ret)
{
	char	ch;
	char	*str_ptr;

	if (*(format + 1) == 'c')
	{
		ch = (char)va_arg(ap, int);
		write(1, &ch, 1);
		(*ret)++;
	}
	else if (*(format + 1) == 's')
	{
		str_ptr = va_arg(ap, char *);
		if (str_ptr == NULL)
		{
			write(1, "(null)", 6);
			*ret += 6;
			return ((char *)(format + 1));
		}
		while (*str_ptr != '\0')
		{
			write(1, str_ptr, 1);
			str_ptr++;
			(*ret)++;
		}
	}
	return ((char *)(format + 1));
}

static char	*address_or_percent(const char *format, va_list ap, int *ret)
{
	char				*str;
	unsigned long long	ptr_addr;
	int					len;
	int					i;

	i = 13;
	if (*(format + 1) == 'p')
	{
		ptr_addr = va_arg(ap, long long);
		len = ft_number_of_digits_3(ptr_addr);
		str = ft_litoa(ptr_addr, len, ret);
		write(1, str, len + 1);
		free(str);
	}
	else if (*(format + 1) == '%')
	{
		write(1, "%%", 1);
		(*ret)++;
	}
	return ((char *)(format + 1));
}

static char	*signed_or_unsigned_int(const char *format, va_list ap, int *ret)
{
	char	*dec_ptr;
	int		i;

	i = 0;
	if (*(format + 1) == 'd' || *(format + 1) == 'i')
	{
		dec_ptr = ft_itoa(va_arg(ap, int));
		while(dec_ptr[i] != '\0')
		{
			write(1, &dec_ptr[i++], 1);
			(*ret)++;
		}
	}
	else if (*(format + 1) == 'u')
	{
		dec_ptr = ft_uitoa(va_arg(ap, int));
		while (dec_ptr[i] != '\0')
		{
			write(1, &dec_ptr[i++], 1);
			(*ret)++;
		}
	}
	free(dec_ptr);
	return ((char *)(format + 1));
}

static char	*upper_or_lower_hex(const char *format, va_list ap, int *ret)
{
	unsigned int	hex;
	char			hex_char[8];
	int				i;

	i = 7;
	hex = va_arg(ap, int);
	while (hex > 0)
	{
		if (9 < hex % 16 && hex % 16 < 16)
		{
			if (*(format + 1) == 'x')
				hex_char[i] = (hex % 16 - 10) + 'a';
			else if (*(format + 1) == 'X')
				hex_char[i] = (hex % 16 - 10) + 'A';
		}
		else
			hex_char[i] = hex % 16 + '0';
		i--;
		hex /= 16;
	}
	if (i < 7)
	{
		write(1, &hex_char[i + 1], 7 - i);
		*ret += (7 - i);
	}
	else
	{
		write(1, "0", 1);
		(*ret)++;
	}
	return ((char *)(format + 1));
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	ret = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (*(format + 1) == 'c' || *(format + 1) == 's')
				format = char_or_str(format, ap, &ret);
			else if (*(format + 1) == 'p' || *(format + 1) == '%')
				format = address_or_percent(format, ap, &ret);
			else if (*(format + 1) == 'd' || *(format + 1) == 'i' || *(format + 1) == 'u')
				format = signed_or_unsigned_int(format, ap, &ret);
			else if (*(format + 1) == 'x' || *(format + 1) == 'X')
				format = upper_or_lower_hex(format, ap, &ret);
		}
		else
		{
			write(1, format, 1);
			ret++;
		}
		format++;
	}
	va_end(ap);
	return (ret);
}

#include <stdio.h>
#include <limits.h>
int main()
{
	char	*name = "chanhyle";
	char	*city = "seoul";
	unsigned int		age = -1230;
	char	grade = 'A';
	int		a;

	a = ft_printf(" %x ", -101);
	printf("%d", a);
	printf("\n");
	a = printf(" %x ", -101);
	printf("%d", a);
	printf("\n");
}
