/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:07:43 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/22 13:07:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	unsigned_digits(unsigned long long unsigned_n, int flag)
{
	int		len;

	len = 0;
	if (unsigned_n == 0)
		len++;
	if (flag == 0)
	{
		while (unsigned_n > 0)
		{
			unsigned_n /= 10;
			len++;
		}
	}
	else
	{
		while (unsigned_n > 0)
		{
			unsigned_n /= 16;
			len++;
		}
	}
	return (len);
}

char	*make_uint_string(unsigned int unsigned_n)
{
	char	*new_str;
	int		len;

	len = unsigned_digits(unsigned_n, 0) + 1;
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '0';
	while (unsigned_n > 0)
	{
		new_str[len - 2] = unsigned_n % 10 + '0';
		unsigned_n /= 10;
		len--;
	}
	return (new_str);
}

char	*make_hex_string(unsigned long long n, int len, int flag)
{
	char	*new_str;

	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '0';
	if (n == 0)
		return (new_str);
	while (n > 0)
	{
		if (9 < n % 16 && n % 16 < 16 && flag == 0)
			new_str[len - 2] = (n % 16 - 10) + 'a';
		else if (9 < n % 16 && n % 16 < 16 && flag == 1)
			new_str[len - 2] = (n % 16 - 10) + 'A';
		else
			new_str[len - 2] = n % 16 + '0';
		n /= 16;
		len--;
	}
	return (new_str);
}
