/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:06:31 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 01:17:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src)
		return (dest);
	if (dest > src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[n - 1] = \
			((const unsigned char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

#include <stdio.h>
#include <string.h>
int main()
{
	char *a = 0;
	char b[] = "asd";

	// printf("%s", (unsigned char *)ft_memmove(b, a, 1));
	printf("%s", (unsigned char *)memmove(b, a, 1));
}
