/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:49:03 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/07 17:49:06 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*type_cs(const char *format, va_list ap, int *ret, t_option *opt)
{
	char	ch;
	char	*str_ptr;

	if (*format == 'c')
	{
		ch = (char)va_arg(ap, int);
		opt->type = 'c';
		print_string_with_option(&ch, ret, opt, 0);
	}
	else if (*format == 's')
	{
		str_ptr = va_arg(ap, char *);
		opt->type = 's';
		if (str_ptr == NULL)
			print_stdin(str_ptr, ret, 0);
		else
		{
			if (opt->width == 0 && opt->dot)
				print_string(str_ptr, ret, opt);
			else
				print_string_with_option(str_ptr, ret, opt, opt->dot);
		}
	}
	return ((char *)format);
}

char	*type_p(const char *format, va_list ap, int *ret, t_option *opt)
{
	unsigned long long	addr;
	char				*addr_ptr;

	if (*format == 'p')
	{
		addr = va_arg(ap, long long);
		opt->type = 'p';
		addr_ptr = make_hex_string(addr, 0);
		addr_ptr = add_prefix(&addr_ptr, 0);
		if (addr_ptr == NULL)
			return (NULL);
		if (opt->width == 0)
			print_string(addr_ptr, ret, opt);
		else
			print_string_with_option(addr_ptr, ret, opt, 0);
		free(addr_ptr);
	}
	else if (*format == '%')
	{
		opt->type = '%';
		print_stdin("%%", ret, 1);
	}
	return ((char *)format);
}

char	*type_int(const char *format, va_list ap, int *ret, t_option *opt)
{
	char	*int_ptr;

	int_ptr = ft_itoa(va_arg(ap, int));
	opt->type = 'd';
	if (int_ptr == NULL)
		return (NULL);
	if (opt->f_zero == 0 && opt->width == 0 && opt->dot == 0
		&& opt->f_space == 0 && opt->f_plus == 0)
		print_string(int_ptr, ret, opt);
	else
		print_string_with_option(int_ptr, ret, opt, 1);
	free(int_ptr);
	return ((char *)format);
}

char	*type_uint(const char *format, va_list ap, int *ret, t_option *opt)
{
	char	*uint_ptr;

	uint_ptr = make_uint_string(va_arg(ap, int));
	opt->type = 'u';
	if (uint_ptr == NULL)
		return (NULL);
	if (opt->f_zero == 0 && opt->width == 0 && opt->prcs == 0)
		print_string(uint_ptr, ret, opt);
	else
		print_string_with_option(uint_ptr, ret, opt, 0);
	free(uint_ptr);
	return ((char *)format);
}

char	*type_hex(const char *format, va_list ap, int *ret, t_option *opt)
{
	unsigned int	hex;
	char			*hex_ptr;
	int				len;

	hex = va_arg(ap, int);
	if (*format == 'x')
		opt->type = 'x';
	else if (*format == 'X')
		opt->type = 'X';
	if (*format == 'x')
		hex_ptr = make_hex_string(hex, 0);
	else if (*format == 'X')
		hex_ptr = make_hex_string(hex, 1);
	if (hex_ptr == NULL)
		return (NULL);
	if (opt->f_sharp && hex_ptr[0] != '0')
		print_base(ret, opt);
	if (opt->f_zero == 0 && opt->width == 0 && opt->dot == 0)
		print_string(hex_ptr, ret, opt);
	else
		print_string_with_option(hex_ptr, ret, opt, 0);
	free(hex_ptr);
	return ((char *)format);
}
