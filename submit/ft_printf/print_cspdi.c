/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cspdi.c                                      :+:      :+:    :+:   */
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
		addr_ptr = malloc_p(addr, ft_unsigned_number_of_digits(addr, 1) + 3);
		if (addr_ptr == NULL)
			return (NULL);
		while (addr_ptr[i] != '\0')
		{
			write(1, &addr_ptr[i], 1);
			i++;
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
