/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:07:58 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/23 20:54:20 by chanhyle         ###   ########.fr       */
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
		print_string(str_ptr, ret);
	}
	return ((char *)(format + 1));
}

char	*print_address_or_percent(const char *format, va_list ap, int *ret)
{
	unsigned long long	addr;
	char				*addr_ptr;

	if (*(format + 1) == 'p')
	{
		addr = va_arg(ap, long long);
		addr_ptr = make_hex_string(addr, 0);
		addr_ptr = add_prefix(&addr_ptr, 0);
		if (addr_ptr == NULL)
			return (NULL);
		print_string(addr_ptr, ret);
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

	int_ptr = ft_itoa(va_arg(ap, int));
	if (int_ptr == NULL)
		return (NULL);
	print_string(int_ptr, ret);
	free(int_ptr);
	return ((char *)(format + 1));
}

char	*print_unsigned_int(const char *format, va_list ap, int *ret)
{
	char	*uint_ptr;

	uint_ptr = make_uint_string(va_arg(ap, int));
	if (uint_ptr == NULL)
		return (NULL);
	print_string(uint_ptr, ret);
	free(uint_ptr);
	return ((char *)(format + 1));
}

char	*print_hex(const char *format, va_list ap, int *ret)
{
	unsigned int	hex;
	char			*hex_ptr;
	int				len;

	hex = va_arg(ap, int);
	if (*(format + 1) == 'x')
		hex_ptr = make_hex_string(hex, 0);
	else if (*(format + 1) == 'X')
		hex_ptr = make_hex_string(hex, 1);
	if (hex_ptr == NULL)
		return (NULL);
	print_string(hex_ptr, ret);
	free(hex_ptr);
	return ((char *)(format + 1));
}
