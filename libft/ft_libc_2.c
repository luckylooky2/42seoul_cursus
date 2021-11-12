/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:44:43 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/12 15:47:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s[cnt])
		cnt++;
	return (cnt);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = 0;
		i++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 && dest == src)
		return (dest);
	while (i < n)
	{
		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	tmp[100000];

	i = 0;
	if (n == 0 && dest == src)
		return (dest);
	while (i < n)
	{
		tmp[i] = *((unsigned char *)src + i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		*((unsigned char *)dest + i) = tmp[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char a[] = "01234567890";
	char b[] = "1123";
	
	printf("%s\n", (unsigned char *)memmove(a+1, b, 5));
	printf("%s\n", (unsigned char *)memmove(a+2, b, 5));
	printf("%s\n", (unsigned char *)memmove(a+3, b, 5));
	printf("%s\n", (unsigned char *)memmove(a+4, b, 5));
	printf("\n");

	char c[] = "01234567890";
	char d[] = "1123";

	printf("%s\n", (unsigned char *)ft_memmove(c+1, d, 5));
	printf("%s\n", (unsigned char *)ft_memmove(c+2, d, 5));
	printf("%s\n", (unsigned char *)ft_memmove(c+3, d, 5));
	printf("%s\n", (unsigned char *)ft_memmove(c+4, d, 5));

	//printf("%s\n", a + 3);
	return 0;
}
*/
