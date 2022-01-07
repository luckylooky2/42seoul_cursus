/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 22:27:17 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/27 22:27:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*print_cs(const char *format, va_list ap, int *ret, t_option *opt)
{
	char	ch;
	char	*str_ptr;

	if (*format == 'c')
	{
		ch = (char)va_arg(ap, int);
		opt->type = 'c';  //opt[8] = 1;
		flag_print_string(&ch, ret, opt, 0);
		(*ret)++;
	}
	else if (*format == 's')
	{
		str_ptr = va_arg(ap, char *);
		opt->type = 's'; //opt[8] = 3;
		if (str_ptr == NULL)
		{
			write_and_plus(str_ptr, ret, 0);
			return ((char *)format);
		}
		if (opt->width == 0 && opt->dot)
			ft_print_string(str_ptr, ret, opt);
		else
			flag_print_string(str_ptr, ret, opt, opt->dot);
	}
	return ((char *)format);
}

char	*print_p(const char *format, va_list ap, int *ret, t_option *opt)
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
			ft_print_string(addr_ptr, ret, opt);
		else
			flag_print_string(addr_ptr, ret, opt, 0);
		free(addr_ptr);
	}
	else if (*format == '%')
	{
		opt->type = '%';
		write_and_plus("%%", ret, 1);
	}
	return ((char *)format);
}

char	*print_int(const char *format, va_list ap, int *ret, t_option *opt)
{
	char	*int_ptr;

	int_ptr = ft_itoa(va_arg(ap, int));
	opt->type = 'd'; //(*opt)[8] = 2
	if (int_ptr == NULL)
		return (NULL);
	if (opt->f_zero == 0 && opt->width == 0 && opt->dot == 0 
		&& opt->f_space == 0 && opt->f_plus == 0)
		ft_print_string(int_ptr, ret, opt);
	else
		flag_print_string(int_ptr, ret, opt, 1);
	free(int_ptr);
	return ((char *)format);
}

char	*print_uint(const char *format, va_list ap, int *ret, t_option *opt)
{
	char	*uint_ptr;

	uint_ptr = make_uint_string(va_arg(ap, int));
	opt->type = 'u'; //(*opt)[8] = 4
	if (uint_ptr == NULL)
		return (NULL);
	if (opt->f_zero == 0 && opt->width == 0 && opt->prcs == 0)
		ft_print_string(uint_ptr, ret, opt);
	else
		flag_print_string(uint_ptr, ret, opt, 0);
	free(uint_ptr);
	return ((char *)format);
}

char	*print_hex(const char *format, va_list ap, int *ret, t_option *opt)
{
	unsigned int	hex;
	char			*hex_ptr;
	int				len;

	hex = va_arg(ap, int);
	if (*format == 'x')
		opt->type = 'x'; //(*opt)[8] = 5
	else if (*format == 'X')
		opt->type = 'X'; //(*opt)[8] = 6
	if (*format == 'x')
		hex_ptr = make_hex_string(hex, 0);
	else if (*format == 'X')
		hex_ptr = make_hex_string(hex, 1);
	if (hex_ptr == NULL)
		return (NULL);
	if (opt->f_sharp && hex_ptr[0] != '0')
		print_sharp(ret, opt);
	if (opt->f_zero == 0 && opt->width == 0 && opt->dot == 0)
		ft_print_string(hex_ptr, ret, opt);
	else
		flag_print_string(hex_ptr, ret, opt, 0);
	free(hex_ptr);
	return ((char *)format);
}
