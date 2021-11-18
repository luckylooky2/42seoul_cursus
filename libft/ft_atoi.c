/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:02:37 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/18 20:51:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	longlong;

	i = 0;
	sign = 1;
	longlong = 0;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
		longlong = longlong * 10 + (nptr[i++] - '0');
	if (sign == -1)
		longlong *= -1;
	if (sign == 1 && (longlong < 0 || i > 19))
		return (-1);
	else if (sign == -1 && (longlong > 0 || i > 19))
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
	// char	n[40] = "-18446744073709551614124";

	// char	*n = "-123THERE IS A NYANCAT UNDER YOUR BED";
	char	n[40] = "-999999999999999999999999999";

	int		i1 = atoi(n);
	int		i2 = ft_atoi(n);

	printf("%d %d\n", i1, i2);
	if (i1 == i2)
		printf("good");
	else
		printf("bad");
}
*/