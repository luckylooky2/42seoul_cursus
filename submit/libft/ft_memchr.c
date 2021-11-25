/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:11:01 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 11:15:10 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*curr;
	size_t				i;

	i = 0;
	curr = 0;
	while (i < n)
	{
		if (((const unsigned char *)s)[i] == (unsigned char)c)
		{
			curr = ((const unsigned char *)s + i);
			break ;
		}
		i++;
	}
	return ((void *)curr);
}
