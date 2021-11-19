/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:10:39 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 15:10:52 by chanhyle         ###   ########.fr       */
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
	char	*ptr;
	int		len;

	if (n == -2147483648)
	{
		ptr = ft_itoa(n + 1);
		ptr[10] = '8';
		return (ptr);
	}
	len = ft_number_of_digits(n);
	ptr = (char *)ft_calloc(len, sizeof(char));
	if (!ptr)
		return (0);
	ptr[0] = '0';
	if (n < 0)
	{
		n *= -1;
		ptr[0] = '-';
	}
	while (n > 0)
	{
		ptr[len-- - 2] = n % 10 + '0';
		n /= 10;
	}
	return (ptr);
}
