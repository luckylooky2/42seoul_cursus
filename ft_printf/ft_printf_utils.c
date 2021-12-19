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

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

int	ft_number_of_digits(unsigned int unsigned_n)
{
	int		len;

	len = 1;
	if (unsigned_n <= 0)
	{
		len++;
		unsigned_n *= -1;
	}
	while (unsigned_n > 0)
	{
		unsigned_n /= 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(int n)
{
	unsigned int	unsigned_n;
	char			*new_str;
	int				len;

	unsigned_n = n;
	len = ft_number_of_digits(unsigned_n);
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '0';
	if (unsigned_n < 0)
	{
		unsigned_n *= -1;
		new_str[0] = '-';
	}
	while (unsigned_n > 0)
	{
		new_str[len-- - 2] = unsigned_n % 10 + '0';
		unsigned_n /= 10;
	}
	return (new_str);
}
