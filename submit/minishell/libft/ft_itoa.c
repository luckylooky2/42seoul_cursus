/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:22:30 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/12 17:57:29 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_str(int n);

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*str;

	if (n == INT32_MIN)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	str = allocate_str(n);
	if (str == 0)
		return (0);
	if (n < 0)
		num = n * -1;
	else
		num = n;
	while (num)
	{
		--str;
		*str = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		return (str - 1);
	else
		return (str);
}

static char	*allocate_str(int n)
{
	char	*str;
	size_t	digits;
	int		temp;
	int		sign;

	digits = 0;
	sign = 0;
	temp = n;
	while (temp)
	{
		++digits;
		temp /= 10;
	}
	if (n <= 0)
		sign = 1;
	str = (char *)malloc(sizeof(char) * (digits + sign + 1));
	if (str == 0)
		return (0);
	if (sign == 1)
		str[0] = '-';
	str[digits + sign] = 0;
	return (str + digits + sign);
}
