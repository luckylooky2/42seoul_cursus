/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:11:22 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/09 23:11:36 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	unsigned char	ch;

	ch = c;
	if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	unsigned char	ch;

	ch = c;
	if ('0' <= ch && ch <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	unsigned char	ch;

	ch = c;
	if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') \
		|| ('0' <= ch && ch <= '9'))
		return (1);
	else
		return (0);
}

int	ft_isascii(int c)
{
	unsigned char	ch;

	ch = c;
	if (ch <= 127)
		return (1);
	else
		return (0);
}

int	ft_isprint(int c)
{
	unsigned char	ch;

	ch = c;
	if (32 <= ch && ch <= 126)
		return (1);
	else
		return (0);
}
