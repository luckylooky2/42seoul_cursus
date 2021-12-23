/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:07:58 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/22 13:08:01 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_char_or_str(const char *format, va_list ap, int *ret)
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
			write(1, str_ptr++, 1);
			(*ret)++;
		}
	}
	return ((char *)(format + 1));
}

char	*print_address_or_percent(const char *format, va_list ap, int *ret)
{
	unsigned long long	addr;
	char				*addr_ptr;
	int					i;

	i = 0;
	if (*(format + 1) == 'p')
	{
		addr = va_arg(ap, long long);
		addr_ptr = make_hex_string(addr, unsigned_digits(addr, 1) + 1, 0);
		if (addr_ptr == NULL)
			return (NULL);
		write(1, "0x", 1);
		while (addr_ptr[i] != '\0')
		{
			write(1, &addr_ptr[i++], 1);
			(*ret)++;
		}
		free(addr_ptr);
	}
	else if (*(format + 1) == '%')
	{
		write(1, "%%", 1);
		(*ret)++;
	}
	return ((char *)(format + 1));
}

char	*print_signed_int(const char *format, va_list ap, int *ret)
{
	char	*int_ptr;
	int		i;

	i = 0;
	int_ptr = ft_itoa(va_arg(ap, int));
	if (int_ptr == NULL)
		return (NULL);
	while (int_ptr[i] != '\0')
	{
		write(1, &int_ptr[i++], 1);
		(*ret)++;
	}
	free(int_ptr);
	return ((char *)(format + 1));
}

char	*print_unsigned_int(const char *format, va_list ap, int *ret)
{
	char	*uint_ptr;
	int		i;

	i = 0;
	uint_ptr = make_uint_string(va_arg(ap, int));
	if (uint_ptr == NULL)
		return (NULL);
	while (uint_ptr[i] != '\0')
	{
		write(1, &uint_ptr[i], 1);
		i++;
		(*ret)++;
	}
	free(uint_ptr);
	return ((char *)(format + 1));
}

char	*print_hex(const char *format, va_list ap, int *ret)
{
	unsigned int	hex;
	char			*hex_ptr;
	int				len;
	int				i;

	i = 0;
	hex = va_arg(ap, int);
	len = unsigned_digits(hex, 1) + 1;
	if (*(format + 1) == 'x')
		hex_ptr = make_hex_string(hex, len, 0);
	else if (*(format + 1) == 'X')
		hex_ptr = make_hex_string(hex, len, 1);
	if (hex_ptr == NULL)
		return (NULL);
	while (hex_ptr[i] != '\0')
	{
		write(1, &hex_ptr[i], 1);
		i++;
		(*ret)++;
	}
	free(hex_ptr);
	return ((char *)(format + 1));
}
