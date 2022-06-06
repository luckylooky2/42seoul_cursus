/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:10:39 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/23 18:50:57 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_number_of_digits(int n)
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
