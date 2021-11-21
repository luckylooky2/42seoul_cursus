/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:12:33 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/21 21:31:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen((char *)src);
	if (size == 0)
		return (size + src_len);
	dest_len = ft_strlen(dest);
	while ((dest_len + 1 + i < size) && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (size != 0)
		dest[dest_len + i] = 0;
	if (size <= dest_len)
		return (size + src_len);
	else
		return (dest_len + src_len);
}

#include <stdio.h>
#include <bsd/string.h>

int main()
{
	char dest[40] = "hello ";
	char src[] = "world";

	printf("%ld", strlcat(dest, src, 2));
	// printf("%ld", strlcat(dest, src, 6));
	// printf("%ld", strlcat(dest, src, 7));
	// printf("%ld", strlcat(dest, src, 8));
	// printf("%ld", strlcat(dest, src, 15));
	printf("%s", dest);
}
