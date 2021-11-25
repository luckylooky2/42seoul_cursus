/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:20:23 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 15:11:57 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long long	longlong;

	if (fd < 0)
		return ;
	longlong = n;
	if (longlong < 0)
	{
		write(fd, "-", 1);
		longlong *= -1;
	}
	if (longlong < 10)
	{
		c = longlong + '0';
		write(fd, &c, 1);
		return ;
	}
	else
	{
		c = longlong % 10 + '0';
		ft_putnbr_fd(longlong / 10, fd);
		write(fd, &c, 1);
	}
}
