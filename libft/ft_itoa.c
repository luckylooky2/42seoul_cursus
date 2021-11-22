/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:13:56 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 01:14:53 by marvin           ###   ########.fr       */
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

#include <stdio.h>
#include <stdlib.h>
int main()
{
	long long a = 222222222222222222;

	printf("%s\n", ft_itoa(a));
	printf("%s\n", itoa(a));
	// printf("%s\n", ft_itoa(-0));
	// printf("%s\n", ft_itoa(-21));
	// printf("%s\n", ft_itoa(1));
	// printf("%s\n", ft_itoa(-1));
	// printf("%s\n", ft_itoa(2147483647));
	// printf("%s\n", ft_itoa(-2147483647));
	// printf("%s\n", ft_itoa(483648111));
	// printf("%s\n", ft_itoa(-218));
	
}

