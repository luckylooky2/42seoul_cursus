/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:02:37 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/18 19:24:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	long long	longlong;

	longlong = 0;
	sign = 1;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
		longlong = longlong * 10 + (*nptr++ - '0');
	if (sign == -1)
		longlong *= -1;
	if (sign == 1 && longlong < 0)
		return (-1);
	else if (sign == -1 && longlong > 0)
		return (0);
	else
		return ((int)longlong);
}

/*
#include <stdio.h>
#include <string.h>
#include <limits.h>
int main()
{
	// char	n[40] = "-18446744073709551614"; //이 이상은 모두 -1 뱉음
	char	n[40] = "+\t\v\f\r\n \f1234";
	// sprintf(n, "%li", LONG_MIN);
	int		i1 = atoi(n);
	int		i2 = ft_atoi(n);

	printf("%d %d\n", i1, i2);
	if (i1 == i2)
		printf("good");
	else
		printf("bad");
}
*/