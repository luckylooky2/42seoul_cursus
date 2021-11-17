/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:59 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 01:16:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		ch;
	const unsigned char	*ptr;
	size_t				i;

	ch = c;
	i = 0;
	ptr = 0;
	while (i < n)
	{
		if (((const unsigned char *)s)[i] == ch)
		{
			ptr = ((const unsigned char *)s + i);
			break ;
		}
		i++;
	}
	return ((void *)ptr);
}
