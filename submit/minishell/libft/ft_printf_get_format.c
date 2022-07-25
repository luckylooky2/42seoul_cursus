/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_format.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 01:29:25 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/17 15:38:40 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_flag(const char **current, t_type *type);
static void	check_width_precision(const char **current, t_type *type);
static char	*form(t_buf *buf, const char **current, t_type *type, va_list *ap);

char	*ft_printf_get_format(t_buf *buf, const char **current, va_list *ap)
{
	t_type	type;

	++*current;
	check_flag(current, &type);
	check_width_precision(current, &type);
	return (form(buf, current, &type, ap));
}

static void	check_flag(const char **current, t_type *type)
{
	type->flag = 0;
	while (**current)
	{
		if (**current == '#')
			type->flag |= ALT;
		else if (**current == '0')
			type->flag |= ZERO;
		else if (**current == '-')
			type->flag |= NEG;
		else if (**current == ' ')
			type->flag |= SPC;
		else if (**current == '+')
			type->flag |= PLUS;
		else
			return ;
		++*current;
	}
}

static void	check_width_precision(const char **current, t_type *type)
{
	type->width = ft_atoi(*current);
	while ('0' <= **current && **current <= '9')
		++*current;
	if (**current == '.')
	{
		++*current;
		type->precision = ft_atoi(*current);
		while ('0' <= **current && **current <= '9')
			++*current;
		if (type->precision == 0)
			type->flag |= NO_DIGIT;
	}
	else
		type->precision = 0;
}

static char	*form(t_buf *buf, const char **current, t_type *type, va_list *ap)
{
	char		*to_return;
	static char	*decimal = "0123456789";
	static char	*low_hex = "0123456789abcdef";
	static char	*up_hex = "0123456789ABCDEF";

	if (**current == 'c')
		to_return = process_char(buf, *type, va_arg(*ap, int));
	else if (**current == 's')
		to_return = process_str(*type, va_arg(*ap, char *));
	else if (**current == 'p')
		to_return = process_ptr(*type, va_arg(*ap, void *));
	else if (**current == 'd' || **current == 'i')
		to_return = process_int(*type, va_arg(*ap, int));
	else if (**current == 'u')
		to_return = process_uint(*type, va_arg(*ap, unsigned int), decimal, 10);
	else if (**current == 'x')
		to_return = process_uint(*type, va_arg(*ap, unsigned int), low_hex, 16);
	else if (**current == 'X')
		to_return = process_uint(*type, va_arg(*ap, unsigned int), up_hex, 16);
	else if (**current == '%')
		to_return = process_char(buf, *type, '%');
	else
		return (0);
	++*current;
	return (to_return);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
