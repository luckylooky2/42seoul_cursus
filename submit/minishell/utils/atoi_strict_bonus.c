/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_strict_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:56:14 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:58:54 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	atoi_s(const char *str, char *flag)
{
	unsigned long	n;
	int				sign;

	*flag = 0;
	n = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
		sign *= 1 - 2 * (*str++ == '-');
	*flag = (char)(*str == 0);
	while (*str == '0')
		str++;
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			n = 10 * n + *str - '0';
		else
			*flag = 1;
		if ((n > 2147483648 && sign == -1) || (n > INT32_MAX && sign == 1))
			*flag = 1;
		str++;
	}
	return (n * sign);
}
