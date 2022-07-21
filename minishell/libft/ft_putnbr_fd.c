/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:23:54 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/12 18:21:08 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_digit_fd(unsigned int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n == INT32_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		num = n * -1;
	}
	else
		num = n;
	put_digit_fd(num, fd);
}

static void	put_digit_fd(unsigned int n, int fd)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(fd, &c, 1);
	}
	else
	{
		put_digit_fd(n / 10, fd);
		put_digit_fd(n % 10, fd);
	}
}
