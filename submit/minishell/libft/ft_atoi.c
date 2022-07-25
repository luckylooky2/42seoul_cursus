/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:19:09 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/12 15:40:43 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isspace(char c);

int	ft_atoi(const char *str)
{
	unsigned long long int	n;
	int						sign;

	while (isspace(*str))
		++str;
	n = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			n = 10 * n + *str - '0';
		else
			break ;
		++str;
	}
	if (n > INT64_MAX - 1 && sign == -1)
		return (0);
	else if (n > INT64_MAX && sign == 1)
		return (-1);
	return (n * sign);
}

static int	isspace(char c)
{
	if (c == '\t' || c == '\r' || c == '\f' || c == '\v' || c == '\n'
		|| c == ' ')
		return (1);
	else
		return (0);
}
