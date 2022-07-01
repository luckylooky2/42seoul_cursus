/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:55:55 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/01 13:48:58 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

long long	ft_atoi(const char *nptr)
{
	int			i;
	long long	longlong;

	i = 0;
	longlong = 0;
	if (!nptr)
		return (0);
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] == '0')
		i++;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		longlong = longlong * 10 + (nptr[i] - '0');
		if ((longlong == INT_MAX / 10) && nptr[i + 1] > ('0' + INT_MAX % 10))
			return (OVER_INT_MAX);
		else if (longlong > INT_MAX / 10
			&& ('0' <= nptr[i + 1] && nptr[i + 1] <= '9'))
			return (OVER_INT_MAX);
		i++;
	}
	return ((int)longlong);
}

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	if (s == NULL)
		return (0);
	while (s[cnt])
		cnt++;
	return (cnt);
}
