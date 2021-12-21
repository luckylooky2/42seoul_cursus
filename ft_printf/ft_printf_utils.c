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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(nmemb * size);
	if (!new_str)
		return (NULL);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)new_str)[i++] = 0;
		return (new_str);
	}
}

int	ft_unsigned_number_of_digits(unsigned long long unsigned_n, int flag)
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

char	*malloc_u(int n)
{
	unsigned int	unsigned_n;
	char			*new_str;
	int				len;

	unsigned_n = n;
	len = ft_unsigned_number_of_digits(unsigned_n, 0) + 1;
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

char	*malloc_p(unsigned long long n, int len)
{
	char	*new_str;

	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '0';
	new_str[1] = 'x';
	new_str[2] = '0';
	if (n == 0)
		return (new_str);
	while (n > 0)
	{
		if (9 < n % 16 && n % 16 < 16)
			new_str[len - 2] = (n % 16 - 10) + 'a';
		else
			new_str[len - 2] = n % 16 + '0';
		n /= 16;
		len--;
	}
	return (new_str);
}

int	ft_number_of_digits(int n)
{
	int		len;

	len = 1;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*new_str;
	int		len;

	if (n == -2147483648)
	{
		new_str = ft_itoa(n + 1);
		new_str[10] = '8';
		return (new_str);
	}
	len = ft_number_of_digits(n);
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '0';
	if (n < 0)
	{
		n *= -1;
		new_str[0] = '-';
	}
	while (n > 0)
	{
		new_str[len-- - 2] = n % 10 + '0';
		n /= 10;
	}
	return (new_str);
}
