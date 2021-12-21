/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:48:19 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/19 15:30:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_unsigned_int(const char *format, va_list ap, int *ret)
{
	char	*uint_ptr;
	int		i;

	i = 0;
	uint_ptr = malloc_u(va_arg(ap, int));
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

static void	print_hex_ptr(char *hex_ptr, int *ret)
{
	int	i;

	i = 0;
	while (hex_ptr[i] != '\0')
	{
		write(1, &hex_ptr[i], 1);
		i++;
		(*ret)++;
	}
}

char	*print_hex(const char *format, va_list ap, int *ret)
{
	unsigned int	hex;
	char			*hex_ptr;
	int				len;

	hex = va_arg(ap, int);
	len = ft_unsigned_number_of_digit(hex, 1) + 1;
	hex_ptr = (char *)ft_calloc(sizeof(char), len);
	if (hex_ptr == NULL)
		return (NULL);
	hex_ptr[0] = '0';
	while (hex > 0)
	{
		if (9 < hex % 16 && hex % 16 < 16 && *(format + 1) == 'x')
			hex_ptr[len - 2] = (hex % 16 - 10) + 'a';
		else if (9 < hex % 16 && hex % 16 < 16 && *(format + 1) == 'X')
			hex_ptr[len - 2] = (hex % 16 - 10) + 'A';
		else
			hex_ptr[len - 2] = hex % 16 + '0';
		hex /= 16;
		len--;
	}
	print_hex_ptr(hex_ptr, ret);
	free(hex_ptr);
	return ((char *)(format + 1));
}
